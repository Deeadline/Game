#pragma once
#include "Player.h"
class Engine
{
public:
	Engine(RenderWindow &win);
	~Engine();
	void runEngine(RenderWindow &win);
private:
	Player player;
};