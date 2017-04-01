#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class Player
{
public:
	Player();
	~Player();
	void setName(string);
	void move(int, int);
	void moveInst(float, float);
	void setPosition(int, int);
	void setTexture(Texture &);
	void draw(RenderWindow &);
	float x(); 
	float y();
	float realX();
	float realY();
	void update(float);
private:
	Vector2f dstPos;
	Vector2f offsetPos;
	string name;
	int hp;
	int strength;
	int intel;
	int agil;
	Texture *texture;
	Sprite sprite;
};