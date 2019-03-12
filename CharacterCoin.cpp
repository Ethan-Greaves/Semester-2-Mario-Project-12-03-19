#include "CharacterCoin.h"

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Render()
{
	SDL_Rect portionOfSpritesheet = { mSingleSpriteWidth * mCurrentFrame, 0,
		mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), 
		mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	//Chnage frame?
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		//Reset Frame delay count 
		mFrameDelay = ANIMATION_DELAY;

		//Move frame on
		mCurrentFrame++;

		//Loop frame around if it goes beyond number of frames
		if (mCurrentFrame > 4)
			mCurrentFrame = 0;
	}
}

void CharacterCoin::setCollected()
{
}

bool CharacterCoin::getCollected()
{
	return false;
}
