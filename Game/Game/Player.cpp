#include "Player.h"
#include <iostream>
using namespace std;
Player::Player()
{
	class_name = "unknown";
	name = "noname";
	hp = mana = 100;
	str = ag = 10;
	exp = 0;
	texture = NULL;
	currentLevel = 0;
}

Player::Player(const Player& player)
{
	this->class_name = player.class_name;
	this->name = player.name;
	this->hp = player.hp;
	this->mana = player.mana;
	this->str = player.str;
	this->ag = player.ag;
	this->exp = player.exp;
	this->texture = NULL;
}

Player::Player(string name, string class_name, int str, int ag)
{
	this->class_name = class_name;
	this->name = name;
	hp = mana = 100;
	this->str = str;
	this->ag = ag;
	exp = 0;
	this->texture = NULL;
}
Player::~Player()
{
	delete texture;
}
void Player::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
	dstPos = Vector2f(x, y);
}
void Player::move(int x, int y)
{
	if (dstPos == Vector2f(realX(), realY()))
	{
		dstPos = Vector2f(x + this->x(), y + this->y());
		offsetPos = Vector2f(x, y);
	}
}
void Player::moveInst(float x, float y)
{
	sprite.move(x, y);
}
void Player::update(float delta)
{
	if (realX() != dstPos.x || realY() != dstPos.y)
	{
		float speed = 2.f;
		delta *= speed;
		moveInst(offsetPos.x*delta, offsetPos.y*delta);
		float eps = 1;
		Vector2f offset = Vector2f(abs(dstPos.x - realX()), abs(dstPos.y - realY()));
		if (offset.x <= eps && dstPos.x != realX())
			setPosition(dstPos.x, realY());
		else if (offset.y <= eps && dstPos.y != realY())
			setPosition(realX(), dstPos.y);
	}
}

void Player::setTexture(Texture &t)
{
	texture = &t;
	sprite.setTexture(*texture);
}
void Player::draw(RenderWindow &window,IntRect &rectSourceSprite)
{
	sprite.setTextureRect(rectSourceSprite);
	window.draw(sprite);
}
float Player::x()
{
	return dstPos.x;
}
float Player::y()
{
	return dstPos.y;
}
float Player::realX()
{
	return sprite.getPosition().x;
}
float Player::realY()
{
	return sprite.getPosition().y;
}
//zmiana broni
void Player::setweapon(Weapon* weapon)
{
	weapon_in_use = *weapon;
}

//zmiana pancerza
void Player::setarmor(Armor* armor)
{
	armor_in_use = *armor;
}

//konstruktor klasy Warrior
Warrior::Warrior() :Player("Warrior", "Warrior", 15, 5)
{
	//ustawienie startowego ekwipunku
	equipment.insert(Weapon("Sword", 1, 1));
	equipment.insert(Armor("Plate armor", 1, 1));
	weapon_in_use = Weapon("Sword", 1, 1);
	armor_in_use = Armor("Plate armor", 1, 1);

	equipment.insert(Weapon("Mace", 1, 1));
	equipment.insert(Weapon("Axe", 1, 1));
}

//konstruktor klasy Mag
Mag::Mag() :Player("Mag", "Mag", 5, 15)
{
	//ustawienie startowego ekwipunku
	equipment.insert(Weapon("Staff", 1, 1));
	equipment.insert(Armor("Robe", 1, 1));
	weapon_in_use = Weapon("Staff", 1, 1);
	armor_in_use = Armor("Robe", 1, 1);
}

//konstruktor klasy Ranger
Ranger::Ranger() :Player("Ranger", "Ranger", 15, 15)
{
	//ustawienie startowego ekwipunku
	equipment.insert(Weapon("Bow", 1, 1));
	equipment.insert(Armor("Leather armor", 1, 1));
	weapon_in_use = Weapon("Bow", 1, 1);
	armor_in_use = Armor("Robe", 1, 1);
}