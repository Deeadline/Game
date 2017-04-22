#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class Player
{
public:
	Player(); //konstruktor
	Player(const Player&); //konstruktor kopiuj¹cy
	Player(string, int, int); // konstruktor
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
	string getname() { return name; } //pobranie imienia
	

	void setstr(int str) { this->str = str; } //ustawienie sily 
	void setag(int ag) { this->ag = ag; } //ustawienie zrecznosci
	void setexp(int exp) { this->exp = exp; } //ustawienie expa
	void sethp(int hp) { this->hp = hp; } //ustawienie hp
	void setmana(int mana) { this->mana = mana; } //ustawienie many
	void setName(string name) { this->name = name; } //ustawiamy nazwe gracza


	void setPosition(int, int); // ustawia pozycje na mapie na poczatku gry
	void setTexture(Texture &); // ustawiamy teksture postaci

protected:
	Vector2f dstPos; // pozycja docelowa gracza
	Vector2f offsetPos; // przesuniêcie o dany wektor
private:
	string name;
	int hp;
	int mana;
	int str;
	int ag;
	int exp;
	Texture *texture;
	Sprite sprite;
};
class Warrior :public Player // klasa wojownik
{
public:
	Warrior() :Player("Warrior", 15, 5) {}
};
class Mag :public Player // klasa mag
{
public:
	Mag() :Player("Mag", 5, 15) {}
};
class Ranger :public Player // klasa lucznik
{
public:
	Ranger() :Player("Ranger", 15, 15) {}
};