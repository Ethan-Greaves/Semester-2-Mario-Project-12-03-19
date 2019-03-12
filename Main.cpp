#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "Character.h"

using namespace std;

//Globals 
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer;
GameScreenManager * gameScreenManager;
Uint32 gOldTime;
Mix_Music * gMusic = NULL;

//Function Prototypes 
bool InitSDL(); //initialise SDL
void CloseSDL();
bool Update();
void LoadMusic(std::string path);

void Render();

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		//Set up the game Screen manager - start with Menu
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		gOldTime = SDL_GetTicks();

		//Set Up Music 
		LoadMusic("Music/Mario.mp3");

		//Flag to check if we wish to quit 
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(gMusic, -1);
			}
			Render();
			quit = Update();
		}
	}

	CloseSDL();
	return 0;
}

//Function Defintions 
bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise. ERROR: " << SDL_GetError();
		return false;
	}
	else
	{
		//Attempt to create a window
		gWindow = SDL_CreateWindow("MyMarioProject", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		//Was the window created?
		if (gWindow == NULL)
		{
			//No
			cout << "Window not created. ERROR: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//Initiilase PNG loading 
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL IMAGE could not init. error" << IMG_GetError();
				return false; 
			}

			//initialise fonts
			/*if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}*/
			
			//Initialise the mixer 
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				std::cout << "Mixer could not initalise. Error: " << Mix_GetError() << std::endl;
				return false;
			}

		}
		else
		{
			cout << "Renderer could not init. error" << SDL_GetError();
			return false;
		}

		//code progresses without a problem, so...
		return true;
	}
}

bool Update()
{
	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler 
	SDL_Event e;

	//Get the events 
	SDL_PollEvent(&e);

	//Handle any events
	switch (e.type)
	{
		//Click the 'X' at top right to quit 
	case SDL_QUIT:
		return true;
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{

		case SDLK_RETURN:
				std::cout << "Enter pressed" << std::endl;
				gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
				break;
		}
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	//set the current time to the old time 
	gOldTime = newTime;
	return false;
}

void LoadMusic(std::string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		std::cout << "Failed to load background music. ERROR: " << Mix_GetError() << std::endl;
	}
}

void Render()
{
	//Clear the screen 
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
}

void CloseSDL()
{
	//Destroy the game screen manager 
	delete gameScreenManager;
	gameScreenManager = NULL;

	//release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release the window 
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Release Music
	Mix_FreeMusic(gMusic); 
	gMusic = NULL;

	//Quit SDL subsystems 
	IMG_Quit();
	SDL_Quit();
	//TTF_Quit();
}