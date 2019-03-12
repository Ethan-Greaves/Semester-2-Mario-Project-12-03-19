#pragma once
#include <iostream>
#include "SDL.h"
#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, LevelMap * map)
		: Character(renderer, imagePath, startPosition, map) 
	{
		mPosition = startPosition;
		mCurrentFrame = 0;
		isCollected = false;
		mSingleSpriteWidth = mTexture->GetWidth() / 5; 
		mSingleSpriteHeight = mTexture->GetHeight();
	};
	~CharacterCoin();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void setCollected();
	bool getCollected();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool isCollected;
	float mFrameDelay;
	int mCurrentFrame;
};

