#pragma once
#include "Character.h"
#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* instance();
	bool Circle(Character * character1, Character * character2);
	bool Box(Rect2D rect1, Rect2D rect2);
	void WindowCollision(Character * character);

private:
	Collisions();
	static Collisions * mInstance;
	Vector2D vec;
	double distance;
	double combinedDistance;
};

