#include "Engine.h"

#include <iostream>
using namespace std;
Engine::Engine(RenderWindow &win, View &vi,Font font,Player& player)
{
	window = &win;
	viewGame = &vi;
	this->font = font;
	this->player = &player;
	IntRect move(32, 0, 32, 48);
	this->move = move;
	// wczytanie kafli do pamiêci
	for (int y = 0, i = 0; y < 2; y++) {
		for (int x = 0; x < 5; x++)
		{
			texture[i].loadFromFile("Data/tileset64.png", IntRect(Vector2i(TILE_SIZE*x, TILE_SIZE*y), Vector2i(TILE_SIZE, TILE_SIZE)));
			i++;
		}
	}
		texture22[0].loadFromFile("Data/Graphic/postacie/symbol1.png"); // trojkat
		texture22[1].loadFromFile("Data/Graphic/postacie/symbol2.png"); // kwadrat
		texture22[2].loadFromFile("Data/Graphic/postacie/symbol3.png"); // kolo
		for(int i=0;i<3;i++)
			texture22[i].createMaskFromColor(Color::White,1);
		for (int i = 0;i < 3;i++)
		{
			texture2[i].loadFromImage(texture22[i]);
			texture2[i].isSmooth();
		}
	// ustawienie wielkoœci tablicy sprite'ów
	WIDTH = window->getSize().x / TILE_SIZE + 2;
	HEIGHT = window->getSize().y / TILE_SIZE + 2;

	Sprite standard(texture[0]);
	sprite.resize(HEIGHT);
	spriteNPC.resize(HEIGHT);
	for (int y = 0; y < HEIGHT; y++) {
		sprite[y].resize(WIDTH, standard);
		spriteNPC[y].resize(WIDTH);
	}

	// ustawienie przykladowej mapy
	setMap("example_level.txt");
}
Engine::~Engine()
{

}
void Engine::runEngine()
{
	bool menu = false;
	// ostatnie rysowanie klatki
	Time lastUpdate = Time::Zero;
	// do mierzenia czasu pomiêdzy klatkami
	float delta;
	while (menu == false)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition(*window));

		window->setView(*viewGame);

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					menu = true;
					clock.restart();
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::A)
				{
						move.left += 32;
						move.top = left * 48;
						if (move.left >= 128)
							move.left = 32;
						if (move.top >= 192)
							move.top = 0;
					movePlayer(-TILE_SIZE, 0);
				}
				else if (event.key.code == Keyboard::D)
				{
						move.left += 32;
						move.top = right * 48;
						if (move.left >= 128)
							move.left = 32;
						if (move.top >= 192)
							move.top = 0;
						movePlayer(TILE_SIZE, 0);
				}
				else if (event.key.code == Keyboard::W)
				{
						move.left += 32;
						move.top = up * 48;
						if (move.left >= 128)
							move.left = 32;
						if (move.top >= 192)
							move.top = 0;
					movePlayer(0, -TILE_SIZE);
				}
				else if (event.key.code == Keyboard::S)
				{
						move.left += 32;
						move.top = down * 48;
						if (move.left >= 128)
							move.left = 32;
						if (move.top >= 192)
							move.top = 0;

					movePlayer(0, TILE_SIZE);
				}
				pair<int, int> temp;
				temp = updateMap();
				updateMapNPC(temp);
				window->setView(*viewGame);
			}
		}
		delta = clock.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
		update(delta);
		player->update(delta);
		lastUpdate = clock.getElapsedTime();
		draw();
	}
}

void Engine::movePlayer(int x, int y)
{
	bool canMove = true;
	Vector2i nextPos(x + player->realX(), y + player->realY());
	nextPos.x /= TILE_SIZE;
	nextPos.y /= TILE_SIZE;

	if (nextPos.x < 0 || nextPos.x >= level.getHeight() || nextPos.y < 0 || nextPos.y >= level.getHeight())
		canMove = false;
	else if (level.map[nextPos.y][nextPos.x].collideable)
		canMove = false;
	else if (npc.NPCMap[nextPos.y][nextPos.x].interactable) {
		if (npc.check(nextPos) == 0)
		{
			npc1 = new Trader();
			cout << "Stworzono Handlarza" << endl;

		}
		else if (npc.check(nextPos) == 1)
		{
			npc1 = new Monster();
			cout << "Stworzono przeciwnika " << endl;
		}
		else if(npc.check(nextPos) == 2)
		{
			npc1 = new Boss();
			cout << "Stworzono bossa" << endl;
		}
	}
	if (canMove)
	{
			player->move(x, y);
			viewGame->move(x, y);
	}
}

void Engine::update(float delta)
{
	//wypisyanie delty
	cout << delta << endl;
}
void Engine::draw()
{
	window->clear();
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			window->draw(sprite[y][x]);
		}
	}
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
				window->draw(spriteNPC[y][x]);
		}
	}

	player->draw(*window,move);
	string str[] = { "Name","Str","Ag" };
	for (int i = 0;i < 3;i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(10);
		text[i].setString(str[i]);
		text[i].setPosition(viewGame->getCenter().x - (viewGame->getSize().x / 2.5), viewGame->getCenter().y - (viewGame->getSize().y / 2.5) + i * 15);
	}
	for (int i = 0;i<3;i++)
		window->draw(text[i]);
	window->display();
}
void Engine::setMap(string name)
{
	// wczytanie mapy i ustawienie wskaŸnika
	if (!level.loadFromFile(name)) {
		cout << "[ERROR] Problem z zaladowaniem poziomu do pamieci!n";
		return;
	}

	if (!tPlayer.loadFromFile("Data/Graphic/Male.png")) cout << "[error] gracz jest nagi!";
	tPlayer.isSmooth();
	this->player->setPosition(level.startX * TILE_SIZE, level.startY* TILE_SIZE);
	this->player->setTexture(tPlayer);


	npc.setMonster(level.getHeight(),level.getWidth(),level);
	pair<int, int> temp;
	temp = updateMap();
	updateMapNPC(temp); 
	window->setView(*viewGame);
}
pair<int,int> Engine::updateMap()
{
	Vector2i fixed(player->x() / TILE_SIZE, player->y() / TILE_SIZE);
	viewGame->setCenter(fixed.x*TILE_SIZE + TILE_SIZE / 2, fixed.y*TILE_SIZE + TILE_SIZE / 2);

	// wyliczamy pozycjê minimalnych granic kamery
	Vector2f min = Vector2f(viewGame->getCenter().x - viewGame->getSize().x / 2, viewGame->getCenter().y - viewGame->getSize().y / 2);

	// ustawienie kamery w poziomie
	int leftBorder = min.x / TILE_SIZE;
	int rightBorder = leftBorder + WIDTH - 2;

	// je¿eli jest za daleko na lewo
	if (min.x < 0)
	{
		int difference = abs(min.x);        // ró¿nica pomiêdzy 0, a lew¹ krawêdzi¹
		min.x += difference;
		viewGame->move(difference, 0);

		leftBorder = min.x / TILE_SIZE;
	}
	else if (leftBorder > 0 && rightBorder - 1 < level.getWidth() - 1)
	{
		min.x -= TILE_SIZE;
		viewGame->move(-TILE_SIZE, 0);

		leftBorder = min.x / TILE_SIZE;
	}

	else if (rightBorder - 1 >= level.getWidth() - 1)
	{
		// MAGIC!
		int difference = viewGame->getCenter().x + viewGame->getSize().x / 2 - (level.getWidth() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.x += difference;

		leftBorder = (min.x) / TILE_SIZE;

		viewGame->setCenter((leftBorder + (WIDTH) / 2)*TILE_SIZE + TILE_SIZE, viewGame->getCenter().y);
	}
	else if (leftBorder == 0)
		viewGame->move(-TILE_SIZE / 2, 0);



	// ustawienie kamery w pionie
	int upBorder = min.y / TILE_SIZE;
	int bottomBorder = upBorder + HEIGHT - 2;

	// analogicznie: je¿eli jest za bardzo wysuniêta do góry
	if (min.y < 0)
	{
		int difference = abs(min.y);
		min.y += difference;
		viewGame->move(0, difference);

		upBorder = min.y / TILE_SIZE;

	}
	else if (upBorder > 0 && bottomBorder - 1 < level.getHeight() - 1)
	{
		min.y -= TILE_SIZE;
		viewGame->move(0, -TILE_SIZE);

		upBorder = min.y / TILE_SIZE;
	}
	else if (bottomBorder - 1 >= level.getHeight() - 1)
	{
		int difference = viewGame->getCenter().y + viewGame->getSize().y / 2 - (level.getHeight() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.y += difference;

		upBorder = (min.y) / TILE_SIZE;

		viewGame->setCenter(viewGame->getCenter().x, (upBorder + (HEIGHT) / 2)*TILE_SIZE + TILE_SIZE);

		if (bottomBorder - 1 == level.getHeight() - 1)           // !!!
			viewGame->move(0, -TILE_SIZE / 2);
	}
	else if (upBorder == 0)
		viewGame->move(0, -TILE_SIZE / 2);

	pair<int,int> temp(upBorder, leftBorder);

	// ustawienie kafli na scenie
	for (int y = 0, h = upBorder; y < HEIGHT; y++) {          // h - horizontal
		for (int x = 0, v = leftBorder; x < WIDTH; x++)       // v - vertical
		{
			sprite[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
			sprite[y][x].setTexture(texture[level.map[h][v].type]);
			v++;
		}
		h++;
	}
	return temp;
}
void Engine::updateMapNPC(pair<int,int> temp)
{
		for (int y = 0, h = temp.first;y < HEIGHT;y++) {
			for (int x = 0, v = temp.second;x < WIDTH;x++) {
				if (npc.NPCMap[h][v].type == NPC::MONSTER)
				{
					spriteNPC[y][x].setPosition(v*TILE_SIZE,h*TILE_SIZE);
					spriteNPC[y][x].setTexture(texture2[npc.NPCMap[h][v].type]);
				}
				if (npc.NPCMap[h][v].type == NPC::TRADER)
				{
					spriteNPC[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
					spriteNPC[y][x].setTexture(texture2[npc.NPCMap[h][v].type]);
				}
				if (npc.NPCMap[h][v].type == NPC::BOSS)
				{
					spriteNPC[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
					spriteNPC[y][x].setTexture(texture2[npc.NPCMap[h][v].type]);
				}
				v++;
			}
			h++;
			
		}
}