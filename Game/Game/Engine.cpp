#include "Engine.h"

#include <iostream>
using namespace std;
Engine::Engine()
{
}
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
		texture2[0].loadFromFile("Data/Graphic/enemy/monk.png"); // trojkat
		texture2[1].loadFromFile("Data/Graphic/enemy/minotaur.png"); // kwadrat
		texture2[2].loadFromFile("Data/Graphic/enemy/redDragon.png"); // kolo
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

	setMap();

	load_equipment();
}
Engine::~Engine()
{

}
string Engine::runEngine()
{
	bool menu = false;
	bool equipment = false;
	bool fight = false;
	// ostatnie rysowanie klatki
	Time lastUpdate = Time::Zero;
	// do mierzenia czasu pomiêdzy klatkami
	float delta;
	while (!menu && !equipment && !fight)
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
					return "menu";
					clock.restart();
				}
				else if (event.key.code == Keyboard::I)
				{
					equipment = true;
					return "equipment";
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
				if (flaga == 1) {
					if (event.type == Event::KeyPressed && event.key.code == Keyboard::Y) {
						fight = true;
						return "fight";
						clock.restart();		
					}
					if (event.type == Event::KeyPressed && event.key.code == Keyboard::N) {
						flaga = false;
						this->canMove = true;
					}
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

bool Engine::action(View& viewMenu)
{
	bool typ;
	if (npc1->action(window, &viewMenu, font,player,&typ)) {
		flaga = 0;
		if (typ) {
			pair<int, int> temp;
			npc.NPCMap[position.y][position.x].exist = false;
			npc.NPCMap[position.y][position.x].interactable = false;
			temp = updateMap();
			updateMapNPC(temp);

			this->canMove = true;
		}
		return false;
	}
	return true;
}

void Engine::movePlayer(int x, int y)
{
	Vector2i nextPos(x + player->realX(), y + player->realY());
	nextPos.x /= TILE_SIZE;
	nextPos.y /= TILE_SIZE;
	if ((nextPos.x < 0 || nextPos.x >= level.getHeight() || nextPos.y < 0 || nextPos.y >= level.getHeight())) {
		this->canMove = false;
	}
	else if (level.map[nextPos.y][nextPos.x].collideable) {
		this->canMove = false;
	}
	else if (npc.NPCMap[nextPos.y][nextPos.x].interactable) {
		position = nextPos;
		flaga = true;
		if (npc.check(nextPos) == 0)
		{
			npc1 = new Trader();
			quest[0].setString("Trade?");
			this->canMove = false;
		}
		else if (npc.check(nextPos) == 1)
		{
			npc1 = new Monster();
			quest[0].setString("Fight?");
			this->canMove = false;
		}
		else if(npc.check(nextPos) == 2)
		{
			npc1 = new Boss();
			quest[0].setString("Fight?");
			this->canMove = false;
		}
	}
	else if (nextPos.x == level.endX && nextPos.y == level.endY) {
		this->canMove = false;
		this->player->setcurrentLevel(1);
		setMap();
	}
	else if (!flaga)
	{
		canMove = true;
	}
		if (this->canMove)
		{
			player->move(x, y);
			viewGame->move(x, y);
		}
}

void Engine::update(float delta)
{
	//wypisyanie delty
	//cout << delta << endl;
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

	player->draw(*window, move);
	string str[] = { "Class name ","Name ","Str ","Ag ", "Weapon ", "Armor " };
	for (int i = 0;i < 6;i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(10);
		text[i].setPosition(viewGame->getCenter().x - (viewGame->getSize().x / 2.5), viewGame->getCenter().y - (viewGame->getSize().y / 2.5) + i * 15);
	}
	
	text[0].setString(str[0] + player->getclassname());
	text[1].setString(str[1] + player->getname());
	text[2].setString(str[2] + to_string(player->getstr()));
	text[3].setString(str[3] + to_string(player->getag()));
	text[4].setString(str[4] + player->getcurrentweapon()->getName());
	text[5].setString(str[5] + player->getcurrentarmor()->getName());
	for (int i = 0;i<6;i++)
		window->draw(text[i]);

	if (flaga) {
		string st[] = { "Question","Yes","No" };
		RectangleShape square;
		square.setPosition(Vector2f(player->realX() + 150, player->realY()));
		square.setFillColor(Color::Transparent);
		quest[0].setFont(font);
		quest[0].setCharacterSize(20);
		quest[0].setPosition(square.getPosition().x,square.getPosition().y);
		for (int i = 1;i < 3;i++)
		{
			quest[i].setFont(font);
			quest[i].setCharacterSize(15);
			quest[i].setString(st[i]);
			quest[i].setPosition(square.getPosition().x, square.getPosition().y+i*30);
		}
		square.setSize(Vector2f(quest[0].getGlobalBounds().height+60,quest[0].getGlobalBounds().width));
		window->draw(square);
		for (int i = 0;i < 3;i++)
			window->draw(quest[i]);
	}

		window->display();
}
void Engine::setMap()
{
	string name = "example_level" + to_string(this->player->getcurrentLevel()) + ".txt";
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
				if (npc.NPCMap[h][v].exist = true) {
					if (npc.NPCMap[h][v].type == NPC::MONSTER)
					{
						spriteNPC[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
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
				}
				v++;
			}
			h++;
			
		}
}
void Engine::load_equipment() {
	global_equipment.insert(Weapon("Sword", 1, 1));
	global_equipment.insert(Weapon("Bow", 1, 1));
	global_equipment.insert(Weapon("Staff", 1, 1));
	global_equipment.insert(Weapon("Mace", 1, 1));
	global_equipment.insert(Weapon("Axe", 1, 1));

	global_equipment.insert(Armor("Plate armor", 1, 1));
	global_equipment.insert(Armor("Leather armor", 1, 1));
	global_equipment.insert(Armor("Robe", 1, 1));
}