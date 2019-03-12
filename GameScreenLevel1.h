#pragma once
#ifndef _GAME_SCEEN_LEVEL_H
#define _GAME_SCEEN_LEVEL_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterLuigi.h"
#include "CharacterCoin.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "Constants.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "SoundEffect.h"

class Texture2D;
class PowBlock;
class Character;
class CharacterKoopa;
class SoundEffect;

class GameScreenLevel1 : public GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();
	void UpdatePowBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

private:
	Texture2D * mBackgroundTexture;
	Texture2D * BlackBackground;
	CharacterMario * myCharacter;
	CharacterLuigi * PlayerTwo;
	LevelMap* mLevelMap;
	PowBlock * mPowBlock;
	CharacterKoopa * koopaCharacter;
	std::vector<CharacterKoopa*> mEnemies;
	Mix_Chunk * SE;
	SoundEffect * Attack;
	CharacterCoin * Coin;

	float RespawnTimer;
	bool SetUpLevel();

	//screenshake variables/function
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	void DoScreenShake();
};

#endif