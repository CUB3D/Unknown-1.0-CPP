#ifndef MAP_H
#define MAP_H

#include "Utils.h"
#include <memory>

namespace Unknown
{
	class Map
	{
	private:
		std::unique_ptr<int[]> map;
		std::unique_ptr<int[]> data;

	public:
		std::unique_ptr<Dimension<int>> mapSize;

		Map(const int width, const int height);

		void setTileID(const int tileID, const int x, const int y);
		int getTileID(const int x, const int y);

		void setData(const int data, const int x, const int y);
		int getData(const int x, const int y);

		const std::unique_ptr<int[]>& getTileMap();
		const std::unique_ptr<int[]>& getData();

		int operator[](int pos);
	};
}

#endif