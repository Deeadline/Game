#pragma once
#include <SFML/Graphics.hpp>
#include "Equipment.h"
#include <string>
using namespace std;
using namespace sf;

class Player
{
public:
	Player(); //konstruktor
	Player(const Player&); //konstruktor kopiuj¹cy
	Player(string, string, int, int); // konstruktor
	~Player(); // destruktor

	//wszystkie podklasy maja dostep do pol prywatnych Playera
	friend class Warrior;
	friend class Mag;
	friend class Ranger;


	void move(int, int); // poruszanie sie plynne
	void moveInst(float, float); // poruszanie sie
	void draw(RenderWindow &,IntRect &); // rysuje naszego gracza

	//pobranie wspó³rzêdnych
	float x();
	float y();
	//pobranie aktualnych wspó³rzêdnych
	float realX();
	float realY();

	void update(float); //aktualizacja polozenia postaci

	//pobranie statystyk gracza
	int getstr() { return str; } //pobranie aktualnej statystyki sila
	int getag() { return ag; } //pobranie aktualnej statystyki zrecznosc
	int getexp() { return exp; } //pobranie expa
	int gethp() { return hp; } //pobranie aktualnego hp
	int getmana() { return mana; } //pobranie aktualnej many

	string getclassname() { return class_name; } // pobranie nazwy klasy postaci
	string getname() { return name; } //pobranie imienia
	Weapon *getcurrentweapon() { return &weapon_in_use; } //pobranie broni
	Armor *getcurrentarmor() { return &armor_in_use; }	//pobranie pancerza
	int getequipmentsize() { return equipment.size(); } //pobranie rozmiaru eq

	void setstr(int str) { this->str = str; } //ustawienie sily 
	void setag(int ag) { this->ag = ag; } //ustawienie zrecznosci
	void setexp(int exp) { this->exp = exp; } //ustawienie expa
	void sethp(int hp) { this->hp = hp; } //ustawienie hp
	void setmana(int mana) { this->mana = mana; } //ustawienie many
	void setName(string name) { this->name = name; } //ustawiamy nazwe gracza
	void setweapon(Weapon*);	//ustawienie broni
	void setarmor(Armor*);		//ustawienie pancerza


	void setPosition(int, int); // ustawia pozycje na mapie na poczatku gry
	void setTexture(Texture &); // ustawiamy teksture postaci

	inline set<Item> getequipment() { return equipment; }

	inline unsigned getcurrentLevel() { return currentLevel; }
	inline void setcurrentLevel(unsigned level) { this->currentLevel = level; }
protected:
	Vector2f dstPos; // pozycja docelowa gracza
	Vector2f offsetPos; // przesuniêcie o dany wektor
private:
	unsigned currentLevel;
	string class_name;
	string name;
	int hp;
	int mana;
	int str;
	int ag;
	int exp;
	Texture *texture;
	Sprite sprite;


	set<Item> equipment;	//ekwipunek postaci
	set<Item>::iterator it;	//iterator do ekwipunku
	Weapon weapon_in_use;	//obecnie uzywana bron
	Armor armor_in_use;		//obecnie uzywany pancerz
};
class Warrior :public Player // klasa wojownik
{
public:
	Warrior();
};
class Mag :public Player // klasa mag
{
public:
	Mag();
};
class Ranger :public Player // klasa lucznik
{
public:
	Ranger();
};