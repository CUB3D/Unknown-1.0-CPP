#include "stdafx.h"
#include "Map.h"

#include "Utils.h"


Unknown::Map::Map(const int width, const int height)
{
    //TODO: Why is this *not* an object
	this->mapSize = std::unique_ptr<Dimension<int>>(new Dimension<int> { width, height });

	this->map = std::unique_ptr<int[]>(new int[width * height]);
	this->data = std::unique_ptr<int[]>(new int[width * height]);
}

void Unknown::Map::setTileID(const int tileID, const int x, const int y)
{
	this->map[mapSize->width * y + x] = tileID;
}

int Unknown::Map::getTileID(const int x, const int y)
{
	return map[mapSize->width * y + x];
}

void Unknown::Map::setData(const int data, const int x, const int y)
{
	this->data[(int)(mapSize->width) * y + x] = data;
}

int Unknown::Map::getData(const int x, const int y)
{
	return data[(int)(mapSize->width) * y + x];
}

const std::unique_ptr<int[]>& Unknown::Map::getTileMap()
{
	return this->map;
}

const std::unique_ptr<int[]>& Unknown::Map::getData()
{
	return this->data;
}

int Unknown::Map::operator[](int pos)
{
	assert(pos > 0);
	assert(pos < mapSize->height * mapSize->width);
	return map[pos];
}