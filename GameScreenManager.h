#pragma once
#ifndef _GAME_SCEEN_MANAGER_H
#define _GAME_SCEEN_MANAGER_H

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"

class GameScreen; //this is forward decleration
class GameScreenMenu;
class GameScreenLevel1;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS newScreen);
	bool getScreen(SCREENS currentScreen);

private:
	SDL_Renderer * mRenderer;
	GameScreen* mCurrentScreen;
	GameScreenLevel1* tempScreen;
	GameScreenMenu* tempMScreen;
};

#endif