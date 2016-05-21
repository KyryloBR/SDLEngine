#ifndef TILESET_H_
#define TILESET_H_

#include "stdafx.h"

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

#endif // TILESET_H_