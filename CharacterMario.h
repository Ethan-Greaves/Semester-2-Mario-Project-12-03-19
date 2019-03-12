#pragma once
#include "Character.h"
#include "Texture2D.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, LevelMap * map) : Character(renderer, imagePath, startPosition, map) {};
	void UpdateKeyboardInput(SDL_Event e);
};

