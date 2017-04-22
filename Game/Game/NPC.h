#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Level.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class NPC
{
public:
	NPC() {} // konstruktor
	~NPC() {} // destruktor

	enum NPCType {
		TRADER,MONSTER,BOSS,DEFAULT,COUNT
	}; // typy przeciwnikow pomocniczo uzywamy DEFAULT by nic nie rysowalo

	//pomocnicza struktura
	struct Npc {
		NPCType type; // typ NPC

		bool interactable; // czy mozna wejsc w interakcje - potrzebne do kolizji
	};

	vector<vector<Npc>> NPCMap; // mapa npc-ow

	void setMonster(int,int,Level &); // funkcja ustawiajaca npc-e na mapie
	int check(Vector2i); // funkcja sprawdzajaca typ npca na danym kafelku - kolizje

	virtual void action() {} // funkcja virtualna - tutaj sa akcje z przeciwnikami
private:
	Npc getNPC(short); // funkcja pomocnicza zwraca rodzaj przeciwnika
};

//KLASY POCHODNE

class Trader :public NPC
{
public:
	Trader():NPC(){}
	void action();
private:
	void trade(); // handel
};
class Monster :public NPC
{
public:
	Monster():NPC(){}
	void action();
	friend class Boss;
private:
	void fight(); // walka
};
class Boss :public NPC
{
public:
	Boss():NPC(){}
	void action();
private:
	void fight(); // walka
};