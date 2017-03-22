#include "Player.h"
Player::Player()
{
	if (!texture.loadFromFile("Data/Graphic/player-move.png"))
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 64, 64));
	sprite.setOrigin(32, 32);
	status = STOJ;
	frame = 0;
	speed = 1.0;
	sprite.setPosition(200, 200);
	anim_clock.restart();
}
Player::~Player() {}
void Player::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}
void Player::update(Vector2f mysz)
{
	Vector2f norm = mysz - sprite.getPosition();
	float rot = atan2(norm.y, norm.x);
	rot = rot * 180.f / M_PI;

	rot += 90;
	sprite.setRotation(rot);

	if (anim_clock.getElapsedTime() > seconds(0.09f))
	{
		if (status == STOJ) return;
		if (frame < 7 /*liczba klatek animacji*/)
			frame++;
		else
			frame = 0; //zapetlanie animacji

		sprite.setTextureRect(IntRect(frame * 64, 0, 64, 64));
		//x, y, szerokosc, wysokosc
		anim_clock.restart();
	}
}
void Player::stop()
{
	status = STOJ;
	frame = 0;
}
void Player::idz(Vector2f mysz)
{
	status = IDZ;
	float rot = sprite.getRotation();
	float vx = sin((rot * M_PI) / 180.0f);
	float vy = -cos((rot * M_PI) / 180.0f);
	sprite.move(speed*vx, speed*vy);
}