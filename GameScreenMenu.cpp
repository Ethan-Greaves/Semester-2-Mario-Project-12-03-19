#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpScreen();
}

bool GameScreenMenu::SetUpScreen()
{
	//Load the menu texture 
	menuBackgroundTexture = new Texture2D(mRenderer);

	if (!menuBackgroundTexture->LoadFromFile("Images/CopytightThis.jpg"))
	{
		std::cout << "Failed to load Menu texture";
		return false;
	}

	return true;
}

GameScreenMenu::~GameScreenMenu()
{
	delete menuBackgroundTexture;
	menuBackgroundTexture = NULL;

	delete gameScreenManager;
	gameScreenManager = NULL;
}

void GameScreenMenu::Render()
{
	//draw the menu background
	menuBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
}







