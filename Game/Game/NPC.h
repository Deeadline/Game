#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include <string>
#include "Level.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
class NPC
{
public:
	NPC() { this->hp = 0; } // konstruktor
	NPC(unsigned hp) { this->hp = hp; }
	~NPC() {} // destruktor
	friend class Boss;
	friend class Monster;
	enum NPCType {
		TRADER,MONSTER,BOSS,DEFAULT,COUNT
	}; // typy przeciwnikow pomocniczo uzywamy DEFAULT by nic nie rysowalo

	//pomocnicza struktura
	struct Npc {
		NPCType type; // typ NPC
		bool interactable; // czy mozna wejsc w interakcje - potrzebne do kolizji
		bool exist;
	};

	vector<vector<Npc>> NPCMap; // mapa npc-ow

	void setMonster(int,int,Level &); // funkcja ustawiajaca npc-e na mapie
	int check(Vector2i); // funkcja sprawdzajaca typ npca na danym kafelku - kolizje
	unsigned gethp() { return hp; }
	virtual bool action(RenderWindow*, View*,Font,Player*, bool ) { return false; } // funkcja virtualna - tutaj sa akcje z przeciwnikami
private:
	Npc getNPC(short); // funkcja pomocnicza zwraca rodzaj przeciwnika
	unsigned hp;
};

//KLASY POCHODNE

class Trader :public NPC
{
public:
	Trader():NPC(0){}
	bool action(RenderWindow*, View*, Font,Player*, bool );
private:
	//void trade(); // handel
};
class Monster :public NPC
{
public:
	Monster() :NPC(100) {}
	bool action(RenderWindow*, View*, Font,Player*, bool );
private:
	//void fight(); // walka
};
class Boss :public NPC
{
public:
	Boss() :NPC(1000) {}
	bool action(RenderWindow*, View*, Font,Player*, bool );
private:
	//void fight(); // walka
};