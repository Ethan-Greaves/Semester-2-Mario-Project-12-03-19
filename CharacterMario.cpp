#include "CharacterMario.h"

void CharacterMario::UpdateKeyboardInput(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;

		case SDLK_d:
			mMovingRight = false;
			break;
		}
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			break;

		case SDLK_d:
			mMovingRight = true;
			break;

		case SDLK_SPACE:
			Jump();
			break;
		}
		break;
	}


}
