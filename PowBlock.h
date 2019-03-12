#pragma once

#include "SDL.h"
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

class LevelMap;
class Texture2D;

class PowBlock
{
public:
	PowBlock(SDL_Renderer * renderer, LevelMap * map);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvailabale() {return mNumberOfHitsLeft > 0;}
	int GetHits();

private:
	SDL_Renderer * mRenderer;
	Vector2D mPosition;
	Texture2D * mTexture;
	LevelMap * mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;

	std::string imagePath;
	int left;

};

