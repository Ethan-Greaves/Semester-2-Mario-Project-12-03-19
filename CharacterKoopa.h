#pragma once
#include "SDL.h"
#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, LevelMap * map, FACING startFacing, float movementSpeed)
		: Character(renderer, imagePath, startPosition, map) 
	{
		mFacingDirection = startFacing;
		mMovementSpeed = movementSpeed;
		mPosition = startPosition;
		mInjured = false;
		mDead = false;
		mSingleSpriteWidth = mTexture->GetWidth() / 2; //2sprites on spritesheet in 1 row
		mSingleSpriteHeight = mTexture->GetHeight();
	};
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void TakeDamage();
	void Jump();
	void SetDead();
	bool GetDead();
	bool IsInjured();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;
	bool mDead;

	void FlipRightWayUp();
};

