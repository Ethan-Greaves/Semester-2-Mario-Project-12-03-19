#pragma once
#ifndef LEVELMAP_H
#define _LEVEL_MAP_H

#include "Constants.h"

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue);

private:
	int** mMap;
};

#endif