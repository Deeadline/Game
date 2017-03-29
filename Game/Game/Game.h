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
	View view;
	Texture backgroundTexture;
	Sprite background;
	void menu(); // g��wne menu
	void menuGame(); // menu z poziomu gry
	void options(); //opcje og�lnie
	void load(); // wczytanie gry z pliku
	void save(); // zapis gry do pliku
	void game(); // g��wne okno gry
	friend void checkConfig(RenderWindow &,View &); // sprawdzenie cfg z pliku
	friend void setResolution(Vector2u,RenderWindow &); // zmiana rozdzielczo�ci
	friend void setSound(); // ON-OFF dzwiek
	friend Texture Set(Texture t,RenderWindow &);//ustawienie t�a
};
#endif