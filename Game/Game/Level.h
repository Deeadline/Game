#pragma once
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <functional>
using namespace std;

class Level
{
public:
	Level(); // destruktor
	~Level(); // konstruktor

	bool loadFromFile(string); // wczytywanie poziomow

	//gettery rozmiaru poziomu
	unsigned short getWidth() { return width; }
	unsigned short getHeight() { return height; }


	// typy kafli
	enum TileType {
		GRASS_1, GRASS_2, GRASS_3, GRASS_4, GRASS_5,
		SAND_1, SAND_2, STONE_1, STONE_2, BUSH, COUNT
	}; // typ kafelkow w grze

	// struktura pomocnicza
	struct Tile {
		TileType type;              // typ kafla potrzebny do rysowania
		string interaction;         // rodzaj interakcji

		bool collideable;           // info o tym czym wywo�uje kolizj�
		bool interactable;          // info o tym czy gracz mo�e wej�� z tym obiektem w interakcj�

		float chance; // szansa na przeciwnika
	};

	// tablica przechowuj�ca informacje o kaflach
	vector < vector <Tile > > map;

	// pozycja startowa gracza (domy�lna na poziom)
	unsigned short startX;
	unsigned short startY;
	unsigned short endX;
	unsigned short endY;

private:
	unsigned short width;           // szerokos� poziomu w kaflach (max 
	unsigned short height;          // wysoko�� poziomu w kaflach

	Tile getTile(short); // funkcja pomocnicza zwraca typ kafelka
};