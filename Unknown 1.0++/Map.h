#ifndef MAP_H
#define MAP_H

#include "Utils.h"
#include <memory>

namespace Unknown
{
	class Map;

	class MapCellProxy {
	private:
		Map& map;
		const int x;
		const int y;

	public:
		MapCellProxy(Map& map, const int x, const int y);

		MapCellProxy& operator=(int rhs);
		MapCellProxy& operator=(MapCellProxy rhs);
		operator int() const;
	};


	class Map
	{
	private:
		std::unique_ptr<int[]> map;
		std::unique_ptr<int[]> data;

	public:
		Dimension<int> mapSize;

		Map(const int width, const int height);

		void setTileID(const int tileID, const int x, const int y);
		int getTileID(const int x, const int y);

		void setData(const int data, const int x, const int y);
		int getData(const int x, const int y);

		bool isOnBoard(const int x, const int y);

		const std::unique_ptr<int[]>& getTileMap();
		const std::unique_ptr<int[]>& getData();

		MapCellProxy operator[](int pos);
		MapCellProxy operator()(int p1, int p2);

		Map& operator=(const Map& other);
	};
}

#endif