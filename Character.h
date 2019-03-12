#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, LevelMap * map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	void AddGravity(float deltaTime);
	void Jump();
	bool IsJumping();
	void CancelJump();
	
	float GetCollisionRadius();
	Rect2D GetCollisionBox();

protected:
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	bool mMovingLeft;
	bool mMovingRight;
	float mCollisionRadius;

	virtual void moveLeft(float deltaTime);
	virtual void moveRight(float deltaTime);

	Texture2D* mTexture;
	SDL_Renderer * mRenderer;
	Vector2D mPosition;
	FACING mFacingDirection;

private:
	int centralXposition;
	int footPosition;
	int headPosition;

	LevelMap* mCurrentLevelMap;
};

#endif