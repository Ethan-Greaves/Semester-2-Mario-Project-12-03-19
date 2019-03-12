#include "Texture2D.h"


Texture2D::Texture2D(SDL_Renderer * renderer)
{
	mRenderer = renderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string path) 
{
	//remove memory used from a previous texture 
	Free();

	//Load the image 
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL) 
	{
		//colour key image - the colour to be transparent 
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		if (mTexture == NULL)
		{
			std::cout << "Unable to create texture from surface. ERROR:  " << SDL_GetError() << std::endl;
		}
		else 
		{
			//set the dimensions 
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}

		//remove loaded surface now that we have our texture 
		SDL_FreeSurface(pSurface);
	}
	else
	{
		std::cout << "Unable to create texture from surface. error: " << IMG_GetError << std::endl;
	}
	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture 
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen 
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}


