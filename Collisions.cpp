#include "Collisions.h"

Collisions * Collisions::mInstance = NULL;

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions * Collisions::instance()
{
	if (!mInstance)
		mInstance = new Collisions;

	return mInstance;
}

bool Collisions::Circle(Character * character1, Character * character2)
{
	vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
		(character1->GetPosition().y - character2->GetPosition().y));

	distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	combinedDistance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width / 2) > rect2.x && (rect1.x + rect1.width / 2) < rect2.x + rect2.width
		&& rect1.y + (rect1.height / 2) > rect2.y && rect1.y + (rect1.height / 2) < rect2.y +
		rect2.height)
	{
		return true;
	}
	return false;
}

void Collisions::WindowCollision(Character * character)
{
	//vertical collision
	if (character->GetPosition().y > SCREEN_HEIGHT - 45)
	{
		character->SetPosition(Vector2D(character->GetPosition().x, SCREEN_HEIGHT - 45));
	}
	
	if (character->GetPosition().y < 0)
	{
		character->SetPosition(Vector2D(character->GetPosition().x, 0));
		character->CancelJump();
	}
	
	//horizontal collision
	if (character->GetPosition().x < 0)
	{
		character->SetPosition(Vector2D(0, character->GetPosition().y));
	}
	
	if (character->GetPosition().x > SCREEN_WIDTH - 30)
	{
		character->SetPosition(Vector2D(SCREEN_WIDTH - 30, character->GetPosition().y));
	}
}
