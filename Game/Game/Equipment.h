#pragma once

#include <string>
#include <set>

using namespace std;

//klasa ogolna przedmiotow
class Item {
	string name;								//nazwa przedmiotu
	unsigned value;								//wartosc przedmiotu
public:
	Item();
	Item(string, unsigned);

	bool is_weapon = false, is_armor = false;

	bool isweapon() const { return is_weapon; }
	bool isarmor() const { return is_armor; }

	string getName() const { return name; }			//pobranie nazwy
	unsigned getValue() const { return value; }		//pobranie wartosci

	bool operator < (const Item&) const;
};

//klasa broni
class Weapon : public Item {
	unsigned damage_value;						//obrazenia broni
public:
	Weapon();
	Weapon(string, unsigned, unsigned);


	unsigned getDamage_value() const { return damage_value; }	//pobranie obrazen broni
};

//klasa pancerzy
class Armor : public Item {
	unsigned armor_value;						//punkty pancerza
public:
	Armor();
	Armor(string, unsigned, unsigned);


	unsigned getArmor_value() const { return armor_value; }	//pobranie punktow pancerza
};
