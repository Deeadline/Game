#include "Engine.h"

Engine::Engine(RenderWindow &win,View &vi)
{
	window = &win;
	viewGame = &vi;
	// wczytanie kafli do pamiêci
	for (int y = 0, i = 0; y < 2; y++) {
		for (int x = 0; x < 5; x++)
		{
			texture[i].loadFromFile("data/tileset64.png", IntRect(Vector2i(TILE_SIZE*x, TILE_SIZE*y), Vector2i(TILE_SIZE, TILE_SIZE)));
			i++;
		}
	}

	// ustawienie wielkoœci tablicy sprite'ów
	WIDTH = window->getSize().x / TILE_SIZE + 2;
	HEIGHT = window->getSize().y / TILE_SIZE + 2;

	Sprite standard(texture[0]);

	sprite.resize(HEIGHT);
	for (int y = 0; y < HEIGHT; y++) {
		sprite[y].resize(WIDTH, standard);
	}

	player = Vector2f(16 * TILE_SIZE, 16 * TILE_SIZE);

	// ustawienie przyk³adowej mapy
	setMap("example_level.txt");
}
Engine::~Engine() {}
void Engine::runEngine()
{
	bool menu = false;
	// ostatnie rysowanie klatki
	Time lastUpdate = Time::Zero;
	// do mierzenia czasu pomiêdzy klatkami
	Clock time;

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
				if (event.key.code == Keyboard::Escape) {
					menu = true;

				}
				if (event.key.code == Keyboard::Left)
				{
					player.x -= TILE_SIZE;
					viewGame->move(-TILE_SIZE, 0);
				}
				else if (event.key.code == Keyboard::Right)
				{
					player.x += TILE_SIZE;
					viewGame->move(TILE_SIZE, 0);
				}
				else if (event.key.code == Keyboard::Up)
				{
					player.y -= TILE_SIZE;
					viewGame->move(0, -TILE_SIZE);
				}
				else if (event.key.code == Keyboard::Down)
				{
					player.y += TILE_SIZE;
					viewGame->move(0, TILE_SIZE);
				}
				updateMap();
				window->setView(*viewGame);
			}
		}

		float delta = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
		update(delta);

		lastUpdate = time.getElapsedTime();
		draw();
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

	window->display();
}
void Engine::setMap(string name)
{
	// wczytanie mapy i ustawienie wskaŸnika
	if (!level.loadFromFile(name)) {
		cout << "[ERROR] Problem z zaladowaniem poziomu do pamieci!n";
		return;
	}

	updateMap();
	window->setView(*viewGame);
}
void Engine::updateMap()
{
	Vector2i fixed(player.x / TILE_SIZE, player.y / TILE_SIZE);
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
}