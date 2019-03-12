#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer * renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;

	//Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//clear up the old screen
	
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}
	
	switch(newScreen)
	{
	case SCREEN_MENU:
		tempMScreen = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)tempMScreen;
		tempMScreen = NULL;
		break;

	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	}
	
}

bool GameScreenManager::getScreen(SCREENS currentScreen)
{
	return currentScreen;
}


