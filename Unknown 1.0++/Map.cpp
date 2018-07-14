#include "stdafx.h"
#include "Map.h"

#include "Utils.h"


Unknown::Map::Map(const int width, const int height)
{
	this->mapSize.width = width;
	this->mapSize.height = height;

	this->map = std::make_unique<int[]>(width * height); //std::unique_ptr<int[]>(new int[width * height]);
	this->data =std::make_unique<int[]>(width * height);// std::unique_ptr<int[]>(new int[width * height]);
}

void Unknown::Map::setTileID(const int tileID, const int x, const int y)
{
	this->map[mapSize.width * y + x] = tileID;
}

int Unknown::Map::getTileID(const int x, const int y)
{
	return map[mapSize.width * y + x];
}

void Unknown::Map::setData(const int data, const int x, const int y)
{
	this->data[(int)(mapSize.width) * y + x] = data;
}

int Unknown::Map::getData(const int x, const int y)
{
	return data[(int)(mapSize.width) * y + x];
}

const std::unique_ptr<int[]>& Unknown::Map::getTileMap()
{
	return this->map;
}

const std::unique_ptr<int[]>& Unknown::Map::getData()
{
	return this->data;
}

Unknown::MapCellProxy Unknown::Map::operator[](int pos)
{
	assert(pos >= 0);
	assert(pos < mapSize.height * mapSize.width);
	int y = pos / mapSize.height;
	int x = pos - y * mapSize.height;
	return MapCellProxy(*this, x, y);
}

Unknown::MapCellProxy Unknown::Map::operator()(int p1, int p2) {
	return MapCellProxy(*this, p1, p2);
}

bool Unknown::Map::isOnBoard(const int x, const int y) {
	return x < mapSize.width && y < mapSize.height && x >= 0 && y >= 0;
}

Unknown::MapCellProxy &Unknown::MapCellProxy::operator=(int rhs) {
	map.setTileID(rhs, x, y);
	return *this;
}

Unknown::MapCellProxy::operator int() const {
	return map.getTileID(x, y);
}

Unknown::MapCellProxy::MapCellProxy(Unknown::Map &map, const int x, const int y) : map(map), x(x), y(y) {}

Unknown::MapCellProxy &Unknown::MapCellProxy::operator=(Unknown::MapCellProxy rhs) {
    map.setTileID((int)rhs, x, y);
    return *this;
}
