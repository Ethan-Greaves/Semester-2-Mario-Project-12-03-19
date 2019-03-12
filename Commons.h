#pragma once
#ifndef _COMMONS_H
#define _COMMONS_H

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float InitialX, float InitialY)
	{
		x = InitialX;
		y = InitialY;
	}
};

struct Rect2D
{
	float x;
	float y;

	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialW, float initialH)
	{
		x = initialX;
		y = initialY;
		width = initialW;
		height = initialH;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT	
};

#endif