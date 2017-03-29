#include "Engine.h"

Engine::Engine(RenderWindow &win,View &vi)
{
	window = &win;
	view = &vi;
	//wczytanie odpowiednich obrazk�w do tablicy texture
	for (int y = 0, i = 0;y < 2;y++) {
		for (int x = 0; x < 5; x++) {
			texture[i].loadFromFile("Data/tileset.png", IntRect(Vector2i(32 * x, 32 * y), Vector2i(32, 32)));
			i++;
		}
	}
	// ustalenie wysoko�ci i szeroko�ci tablicy sprite'�w
	WIDTH = window->getSize().x / 32 + 2;
	HEIGHT = window->getSize().y / 32 + 2;
	cout << "WIDTH:" << WIDTH << " HEIGHT:" << HEIGHT << endl;
	//powi�kszenie owej tablicy do WIDTH i HEIGHT
	Sprite standard(texture[0]);
	sprite.resize(HEIGHT);
	for (int y = 0; y < HEIGHT; y++) {
		sprite[y].resize(WIDTH, standard);
	}
	// ustawienie gracza na danej pozycji
	player = Vector2f(16 * 32, 16 * 32);
	// wczytanie mapy
	setMap("Level.level");
}
Engine::~Engine() {}
void Engine::runEngine()
{
	Time lastUpdate = Time::Zero;
	Clock time;
	bool menu = false;
	window->clear();
	window->display();
	while (!menu)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition(*window));
		while (window->pollEvent(event))
		{
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Escape){
					menu = true;
					FloatRect x(0, 0, 1024, 768);
					view->reset(x);

				}
				if (event.key.code == Keyboard::D)
				{
					player.x += 32;
					view->move(32, 0);
				}
				if (event.key.code == Keyboard::W)
				{
					player.y -= 32;
					view->move(0, -32);
				}
				if (event.key.code == Keyboard::A)
				{
					player.x -= 32;
					view->move(-32,0);
				}
				if (event.key.code == Keyboard::S)
				{
					player.y += 32;
					view->move(0, 32);
				}
				updateMap();
				window->setView(*view);
			}
		}
		float delta = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
		update(delta);
		lastUpdate = time.getElapsedTime();
		//draw();
		window->clear();
		window->draw(sprite[0][0]);
		window->display();
	}
}
void Engine::update(float delta)
{
	//wypisyanie delty
	cout << delta << endl;
}
void Engine::draw()
{
	//rysowanie mapy
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
	//wczytanie poziomu
	if (!level.loadFromFile(name)) {
		cout << "Nie wczytano poziomu" << endl;
		return;
	}
	//ustawienie mapy i view.
	updateMap();
	window->setView(*view);
}
void Engine::updateMap()
{
	//ustawienie widoku mapy
	Vector2i fixed((int)player.x / 32, (int)player.y / 32);
	view->setCenter(fixed.x * 32 + 32 / 2, fixed.y * 32 + 32 / 2);
	Vector2f min = Vector2f(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2);

	float left = min.x / (float)32.0;
	float right = left + WIDTH - 2;
	if (min.x < 0)
	{
		float diff = abs(min.x);
		min.x += diff;
		view->move(diff, 0);
		left = min.x / (float)3.0;
	}
	else if (left > 0 && right - 1 < level.getW() - 1)
	{
		min.x -= 32;
		view->move(-32, 0);
		left = min.x / 32;
	}
	else if (right - 1 >= level.getW() - 1)
	{
		float diff = view->getCenter().x + view->getSize().x / 2 - (level.getW() - 1) * 32;
		diff = -diff - 32;
		min.x += diff;
		left = min.x / 32;
		view->setCenter((float)((left + (WIDTH) / 2) * 32 + 32), (float)(view->getCenter().y));
	}
	else if (left == 0)
		view->move((float)(-32 / 2), (float)0);
	float upBorder = min.y / 32;
	float bottomBorder = upBorder + HEIGHT - 2;

	if (min.y < 0) {
		float diff = abs(min.y);
		min.y += diff;
		view->move(0, diff);

		upBorder = min.y / 32;
	}
	else if (upBorder > 0 && bottomBorder - 1 < level.getH() - 1)
	{
		min.y -= 32;
		view->move(0, -32);

		upBorder = min.y / 32;
	}
	else if (bottomBorder - 1 >= level.getH() - 1)
	{
		int difference = view->getCenter().y + view->getSize().y / 2 - (level.getH() - 1) * 32;

		difference = -difference - 32;
		min.y += difference;

		upBorder = (min.y) / 32;

		view->setCenter(view->getCenter().x, (upBorder + (HEIGHT) / 2) * 32 + 32);

		if (bottomBorder - 1 == level.getH() - 1)
			view->move(0, -32 / 2);
	}
	else if (upBorder == 0)
		view->move(0, -32 / 2);


	// ustawienie kafli na scenie
	for (int y = 0, h = upBorder; y < HEIGHT; y++) {          // h - horizontal
		for (int x = 0, v = left; x < WIDTH; x++)       // v - vertical
		{
			sprite[y][x].setPosition(v * 32, h * 32);
			sprite[y][x].setTexture(texture[level.map[h][v].type]);

			v++;
		}
		h++;
	}
}
