#include "Character.h"

Character::Character(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, LevelMap * map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mPosition = startPosition;

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load character sprite(s)";
	}

	mCurrentLevelMap = map;

	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;

	mCollisionRadius = 15.0f;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE); 

	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	centralXposition = (int)(mPosition.x + mTexture->GetWidth() * 0.5f) / TILE_WIDTH;
	footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	headPosition = (int)(mPosition.y + mTexture->GetHeight() * 0.5f) / TILE_HEIGHT;

	//allows character to fall back down to ground/tile
	if(mCurrentLevelMap->GetTileAt(footPosition, centralXposition) == 0)
		AddGravity(deltaTime);
	else
	{
		//Collided with ground so we can jump again
		mCanJump = true;
	}

	if (mCurrentLevelMap->GetTileAt(headPosition, centralXposition) == 2)
	{
		std::cout << "mario hitting tunnel" << std::endl;
		
	}

	//Deal with jumping first
	if (mJumping)
	{
		//Adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce the jump force 
		mJumpForce -= deltaTime * JUMP_FORCE_DECREMENT;

		//Has the jump force reduced to zero?
		if (mJumpForce <= 0.0f)
		{
			mJumping = false; //todo when mJumping is false that makes mCanJump true which allows infinite jumping
		}
	}
	
	if (mMovingLeft)
	{
		moveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		moveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void  Character::AddGravity(float deltaTime)
{
		mPosition.y += deltaTime * GRAVITY;
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = true;
	}
}

bool Character::IsJumping()
{
	if (mJumpForce > 0.0f)
		return true;
	else
		return false;
}

void Character::CancelJump()
{
	mJumpForce = 0.0f;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void Character::moveLeft(float deltaTime)
{
	mPosition.x -= deltaTime * MOVEMENT_SPEED;
	mFacingDirection = FACING_LEFT;
}

void Character::moveRight(float deltaTime)
{
	mPosition.x += deltaTime * MOVEMENT_SPEED;
	mFacingDirection = FACING_RIGHT;
}
