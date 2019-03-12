#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer * renderer, LevelMap * map)
{
	imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cerr << "Failed to Load PowBlock texture" << std::endl;
		return;
	}

	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; // 3 sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5) - mSingleSpriteWidth * 0.5, 260);
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;

	mLevelMap = NULL;
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		//Get the portion of the spritesheet you want to draw 
		left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		//
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//determine where you want it drawn
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		//draw
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}

}

int PowBlock::GetHits()
{
	return mNumberOfHitsLeft;
}
