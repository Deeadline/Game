#pragma once
#include "Level.h"
#include <fstream>
#include <iostream>
using namespace std;
Level::Level()
{
	width = height = startX = startY = 0;
}
Level::~Level()
{

}
Level::Tile Level::getTile(short number)
{
	Tile tile;
	tile.type = TileType(number);
	switch (TileType(number))
	{
	case Level::STONE_1:
		tile.collideable = true;
		tile.interactable = false;
		break;
	case Level::STONE_2:
		tile.collideable = true;
		tile.interactable = false;
		break;
	case Level::BUSH:
		tile.collideable = true;
		tile.interactable = false;
		break;
	default:
		tile.collideable = false;
		tile.interactable = false;
		break;
	}
	return tile;
}

bool Level::loadFromFile(string Level_Name)
{
	fstream file;
	file.open("Data/" + Level_Name);
	if (!file.is_open()) return false;
	file >> width >> height;
	if (width == 0 || height == 0) {
		file.close();
		return false;
	}
	map.resize(height);
	for (int i = 0; i < height; i++) {
		map[i].resize(width);
	}
	for (int y = 0;y < height; y++) {
		for (int x = 0;x < width; x++) {
			short buff;
			file >> buff;
			map[y][x] = getTile(buff);
			cout << buff << " ";
		}
		cout << endl;
	}
	while (!file.eof())
	{
		string name;
		file >> name;
		short x, y;
		file >> x >> y;
		if (name == "[Start]") {
			map[y][x].interaction = name;
			if (startX == 0 && startY == 0) {
				startX = x;
				startY = y;
			}
		}
		else {
			map[y][x].interaction = name;
			map[y][x].interactable = true;
		}
	}
	file.close();
	return true;
}


int Level::getW()
{
	return width;
}


int Level::getH()
{
	return height;
}
