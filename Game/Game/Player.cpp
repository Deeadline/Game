#include "Player.h"

Player::Player()
{
	name = "noname";
	hp = 100;
	strength = intel = agil = 10;
	texture = NULL;
}
Player::~Player()
{

}
void Player::setName(string name)
{
	this->name = name;
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
		float speed = 1.75f;
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
void Player::draw(RenderWindow &window)
{
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
