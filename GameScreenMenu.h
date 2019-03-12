#pragma once

#include "Texture2D.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"

class GameScreenManager;

class GameScreenMenu : public GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	bool SetUpScreen();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	
private:
	Texture2D * menuBackgroundTexture;
	GameScreenManager * gameScreenManager;

	Vector2D bPosition;
};

