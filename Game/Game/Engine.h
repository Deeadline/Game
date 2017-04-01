#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Game.h"
#include "Level.h"
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
	void draw();
	Texture texture[Level::COUNT];
	Level level;
	vector<vector<Sprite>> sprite;
	int WIDTH, HEIGHT;
	short TILE_SIZE = 64;
	void setMap(string);
	Vector2f player;
	RenderWindow *window;
	View *viewGame;
};
#endif