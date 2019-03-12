#include "CharacterKoopa.h"

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//If injured move the left position to be the left position of the second image of the sprite sheet 
	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	//Get portion of sprite sheet we want to draw
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//draw it facing correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//To gain benefit of code written in base class update func; we need to call it.
	Character::Update(deltaTime, e);

	if (mInjured == false)
	{
		//Not Injured so move
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
		else
		{
			//Should not be moving when injured 
			mMovingRight = false;
			mMovingLeft = false;

			mInjuredTime -= deltaTime;

			if (mInjuredTime <= 0.0)
				FlipRightWayUp();
		}
	
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::SetDead()
{
	mDead = true;
}

bool CharacterKoopa::GetDead()
{
	return mDead;
}

bool CharacterKoopa::IsInjured()
{
	return mInjured;
}

void CharacterKoopa::FlipRightWayUp()
{
	
	if (mFacingDirection = FACING_LEFT)
	{
		mFacingDirection = FACING_RIGHT;
	}
	else if (mFacingDirection = FACING_RIGHT)
	{
		mFacingDirection = FACING_LEFT;
	}
	
	mInjured = false;
	//Jump();

}
