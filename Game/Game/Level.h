#pragma once
#include <string>
#include <vector>

using namespace std;

class Level
{
public:
	Level();
	~Level();

	bool loadFromFile(string);

	// typy kafli
	enum TileType {
		GRASS_1, GRASS_2, GRASS_3, GRASS_4, GRASS_5,
		SAND_1, SAND_2, SAND_3, STONE_1, STONE_2, BUSH, COUNT
	};

	// struktura pomocnicza
	struct Tile {
		TileType type;              // typ kafla potrzebny do rysowania
		string interaction;         // rodzaj interakcji

		bool collideable;           // info o tym czym wywo³uje kolizjê
		bool interactable;          // info o tym czy gracz mo¿e wejœæ z tym obiektem w interakcjê
	};

	// tablica przechowuj¹ca informacje o kaflach
	vector < vector <Tile > > map;

	// pozycja startowa gracza (domyœlna na poziom)
	unsigned short startX;
	unsigned short startY;

	unsigned short getWidth() { return width; }
	unsigned short getHeight() { return height; }


private:
	unsigned short width;           // szerokosæ poziomu w kaflach (max 
	unsigned short height;          // wysokoœæ poziomu w kaflach

	Tile getTile(short);
};