#include "level.h"
#include <fstream>
#include <iostream>
using namespace std;
Level::Level()
{
	width = 0;
	height = 0;

	startX = 0;
	startY = 0;

	endX = 0;
	endY = 0;
}


Level::~Level()
{
}

// funkcja pomocnicza, zwraca Tile o odpowiednich w³aœciwoœciach
Level::Tile Level::getTile(short code)
{
	Tile tile;
	tile.type = TileType(code);

	switch (TileType(code))
	{
	case Level::STONE_1:
		tile.collideable = true;
		tile.interactable = false;
		tile.chance = 0.0;
		break;

	case Level::STONE_2:
		tile.collideable = true;
		tile.interactable = false;
		tile.chance = 0.0;
		break;

	case Level::GRASS_1:
		tile.collideable = false;
		tile.interactable = true;
		tile.chance = 0.90;
		break;

	default:
		tile.collideable = false;
		tile.interactable = true;
		tile.chance = 0.0;
		break;
	}

	return tile;
}

// Zwraca "true" je¿eli uda³o siê pomyœlnie wczytaæ plik
bool Level::loadFromFile(string level_name)
{
	fstream file;
	file.open("Data/" + level_name);

	if (!file.is_open())
		return false;

	// wczytywanie rozmiarów poziomu
	file >> width >> height;

	if (width == 0 || height == 0) {
		file.close();
		return false;
	}

	// ustawiamy sobie rozmiary tablicy
	map.resize(height);
	for (int i = 0; i < height; i++) {
		map[i].resize(width);
	}

	// wczytujemy kafelki
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			short buffer;

			file >> buffer;
			map[y][x] = getTile(buffer);
		}
	}

	// wczytujemy pozosta³e eventy
	while (!file.eof())
	{
		string name;        // nazwa specjalnego obiektu
		file >> name;

		unsigned short x, y;
		file >> x >> y;
		if (name == "[START]") {
			// ustawienie interakcji
			map[y][x].interaction = name;

			// ustawienie jako standardowe wejœcie
			if (startX == 0 && startY == 0) {
				startX = x;
				startY = y;
			}

		}

		else if(name == "[EXIT]"){
			map[y][x].interaction = name;
			endX = x;
			endY = y;

		}
		else {
			map[y][x].interactable = true;
			map[y][x].interaction = name;
		}
	}

	file.close();
	return true;
}

