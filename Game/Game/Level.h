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
	enum TileType {
		GRASS_1,GRASS_2,GRASS_3,GRASS_4,GRASS_5,
		SAND_1,SAND_2,STONE_1,STONE_2,BUSH,COUNT
	};
	struct Tile {
		TileType type;
		string interaction;
		bool collideable, interactable;
	};
	vector< vector<Tile>> map;
	short startX, startY;
	int getW();
	int getH();
private:
	int width, height;
	Tile getTile(short);
};