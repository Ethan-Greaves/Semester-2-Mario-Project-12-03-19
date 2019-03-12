#pragma once
#include "Character.h"
#include "Texture2D.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, LevelMap * map) 
		: Character(renderer, imagePath, startPosition, map) {};
	void UpdateKeyboardInput(SDL_Event e);
};

