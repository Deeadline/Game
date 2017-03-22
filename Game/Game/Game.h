#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Engine.h"
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
	Texture tex1;
	Sprite tlo;
	void menu(); // g��wne menu
	void menuGame(); // menu z poziomu gry
	void options(); //opcje og�lnie
	void load(); // wczytanie gry z pliku
	void save(); // zapis gry do pliku
	void game(); // g��wne okno gry
	friend void checkConfig(); // sprawdzenie cfg z pliku
	friend void setResolution(Vector2u); // zmiana rozdzielczo�ci
	friend void setSound(); // ON-OFF dzwiek
	friend Texture Set(Texture t);
};