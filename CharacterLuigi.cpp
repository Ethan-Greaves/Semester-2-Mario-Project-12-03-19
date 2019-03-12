#include "CharacterLuigi.h"

void CharacterLuigi::UpdateKeyboardInput(SDL_Event e) //TODO change this just to update, call character update, use polymorphism
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;

		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			break;

		case SDLK_RIGHT:
			mMovingRight = true;
			break;

		case SDLK_UP:
			Jump();
			break;
		}
		break;
	}
}
