#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <sftools\Chronometer.hpp>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level.h"
#include "Player.h"
using namespace std;
using namespace sf;
class Game
{
public:

	Game(); // konstruktor
	~Game(); // destruktor
	void runGame(); // glowna funkcja

protected:
	enum GameState {MENU,OPTIONS,GAME,MGAME,CHSELECTION,SAVE,LOAD,END}; // stany gry
	GameState state; // zmienna przechowujaca stan gry
private:
	Font font; // czcionka
	RenderWindow window; // okno
	View viewMenu,viewGame; // widok w menu i w grze
	Texture backgroundTexture; // tekstura tla
	Sprite background; // tlo
	Player* player; // polimorfizm gracza

	void menu(); // g³ówne menu
	void menuGame(); // menu z poziomu gry
	void options(); //opcje ogólnie
	void load(); // wczytanie gry z pliku
	void save(); // zapis gry do pliku
	void select(); // okno wyboru postaci

	void game(); // g³ówne okno gry

	void checkConfig(); // sprawdzenie cfg z pliku
	void setResolution(Vector2u); // zmiana rozdzielczoœci
	void setSound(); // ON-OFF dzwiek

	Texture Set(Texture t);//ustawienie t³a

};
#endif