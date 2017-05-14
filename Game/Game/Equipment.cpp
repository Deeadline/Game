#include "Equipment.h"

Item::Item() {
	name = "NULL";
	value = 0;
}

Item::Item(string name, unsigned value) {
	this->name = name;
	this->value = value;
}

bool Item::operator < (const Item& item) const {
	if (this->name < item.name)
		return true;
	return false;
}

////////////////////////////////////////////////////////////

Weapon::Weapon() : Item() {
	damage_value = 0;
}

Weapon::Weapon(string name, unsigned value, unsigned damage_value)
	: Item(name, value) {
	this->damage_value = damage_value;
	this->is_weapon = true;
}

////////////////////////////////////////////////////////////

Armor::Armor() : Item() {
	armor_value = 0;
}

Armor::Armor(string name, unsigned value, unsigned armor_value)
	: Item(name, value) {
	this->armor_value = armor_value;
	this->is_armor = true;
}
