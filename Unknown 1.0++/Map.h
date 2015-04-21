#ifndef MAP_H
#define MAP_H

#include "Utils.h"

namespace Unknown
{
	class Map
	{
	private:
		int* map;
		int* data;

	public:
		const Dimension* mapSize;

		Map(const int width, const int height);
		~Map();

		void setTileID(const int tileID, const int x, const int y);
		int getTileID(const int x, const int y);

		void setData(const int data, const int x, const int y);
		int getData(const int x, const int y);

		const int* getTileMap();
		const int* getData();
	};
}

#endif