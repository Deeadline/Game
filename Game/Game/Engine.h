#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Game.h"
#include "Level.h"
#include "Player.h"
#include "NPC.h"
using namespace sf;
class Engine
{
public:
	Engine(RenderWindow &win, View &view,Font font,Player&); // konstruktor
	~Engine(); // destruktor
	void runEngine(); // mechanika poruszania sie po planszy
protected:
	enum moving{down,left,right,up}; // typ do poruszania sie
	IntRect move; // typ do poruszania sie
private:
	pair<int,int> updateMap(); // aktualizacja mapy co klatke zwraca nam polozenie kamery
	void update(float); // aktualizacja delty
	void movePlayer(int, int); // poruszanie sie gracza po planszy oraz kolizje
	void draw(); // rysowanie sie planszy i elementow
	void updateMapNPC(pair<int,int>); // aktualizacja mapy NPC
	void setMap(string); // ustaw mape

	int WIDTH, HEIGHT; // szer,wys
	short TILE_SIZE = 64; // rozmiar kafelka
	Texture texture[Level::COUNT]; // teksturki mapy
	Image texture22[NPC::COUNT]; // teksturki NPC 
	Texture texture2[NPC::COUNT];
	vector<vector<Sprite>> sprite; // mapa
	vector<vector<Sprite>> spriteNPC; // rozmieszczenie NPC 

	Clock clock; // czas
	NPC npc; // mapa npc
	NPC* npc1; // polimorficzny npc
	Level level; // poziom
	Texture tPlayer; // tekstura gracza
	Texture rWindow;	Sprite test;
	Player* player; // gracz
	RenderWindow *window; // okno
	View *viewGame; // widok gry
	Font font; // czcionka
	Text text[3]; //tekst wyswietlajacy statystyki
	Text question[3]; // pytanie
};
#endif