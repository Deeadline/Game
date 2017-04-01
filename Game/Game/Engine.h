#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Game.h"
#include "Level.h"
#include "Player.h"
using namespace sf;
class Engine
{
public:
	Engine(RenderWindow &win,View &view);
	~Engine();
	void runEngine();
private:
	void updateMap();
	void update(float);
	void movePlayer(int, int);
	void draw();
	Texture texture[Level::COUNT];
	Level level;
	vector<vector<Sprite>> sprite;
	int WIDTH, HEIGHT;
	short TILE_SIZE = 64;
	short TILE_SIZE1 = 32;
	void setMap(string);
	Texture tPlayer;
	Player player;
	RenderWindow *window;
	View *viewGame;
};
#endif