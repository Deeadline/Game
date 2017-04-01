#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level.h"
using namespace std;
using namespace sf;
class Game
{
public:
	Game();
	~Game();
	void runGame(); // glowna funkcja
protected:
	enum GameState {MENU,OPTIONS,GAME,MGAME,SAVE,LOAD,END};
	GameState state;
private:
	Font font;
	RenderWindow window;
	View viewMenu,viewGame;
	Texture backgroundTexture;
	Sprite background;

	void menu(); // g³ówne menu
	void menuGame(); // menu z poziomu gry
	void options(); //opcje ogólnie
	void load(); // wczytanie gry z pliku
	void save(); // zapis gry do pliku

	void game(); // g³ówne okno gry

	void checkConfig(); // sprawdzenie cfg z pliku
	void setResolution(Vector2u); // zmiana rozdzielczoœci
	void setSound(); // ON-OFF dzwiek

	Texture Set(Texture t);//ustawienie t³a
};
#endif