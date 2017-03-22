#include "Game.h"
#include <fstream>

RenderWindow window;
Texture Set(Texture t)
{
	if (window.getSize().x == 800) t.loadFromFile("Data/Graphic/1.png");
	else if (window.getSize().x == 1024) t.loadFromFile("Data/Graphic/2.png");
	else if (window.getSize().x == 1600) t.loadFromFile("Data/Graphic/3.png");
	return t;
}
void setResolution(Vector2u x)
{
	fstream plik;
	plik.open("Data/config.cfg", ios::out | ios::trunc);
	window.create(VideoMode(x.x, x.y), "Robocza nazwa gry", Style::Close);
	plik << (int)x.x << ',' << (int)x.y ;
	plik.close();
}
void checkConfig()
{
	fstream plik;
	plik.open("Data/config.cfg", ios::in|ios::out);
	if (!plik.is_open())
	{
		MessageBox(NULL, "Config not found!", "ERROR", NULL); 
		return;
	}
	string data;
	getline(plik, data);
	size_t pos = data.find(',');
	int x = atoi(data.substr(0, pos).c_str());
	data.erase(0, pos + 1);
	int y = atoi(data.c_str());
	plik.close();
	window.create(VideoMode(x, y), "Robocza nazwa gry", Style::Close);
}
Game::Game()
{
	ContextSettings set;
	set.antialiasingLevel = 8;
	checkConfig();
	tex1 = Set(tex1);
	tlo.setTexture(tex1);
	state = END;
	window.setFramerateLimit(100);
	if (!font.loadFromFile("Data/Roboto.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL); return;
	}
	state = MENU;
}
Game::~Game() {}
void Game::runGame()
{
	while (state != END)
	{
		switch (state) {
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			game();
			break;
		case GameState::OPTIONS:
			options();
			break;
		case GameState::LOAD:
			load();
			break;
		case GameState::MGAME:
			menuGame();
			break;
		case GameState::SAVE:
			save();
			break;
		}
	}
}
void Game::menu()
{
	Text title("Robocza nazwa gry", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getDefaultView().getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	const int count = 4;
	Text text[count];
	string str[] = { "Play","Load","Options","Exit" };
	for (int i = 0;i < count;i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(30);
		text[i].setString(str[i]);
		cout << text[i].getGlobalBounds().width << " ";
		text[i].setPosition(50, (250 + i * 50));
	}
	while (state == MENU) 
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed
				&& event.key.code == Keyboard::Escape) {
				state = END;
			}
			else if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = GAME;
			}
			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = LOAD;
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = OPTIONS;
			}
			else if (text[3].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
		for (int i = 0;i < count;i++) {
			if(text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Green);
			else text[i].setFillColor(Color::Yellow);
		}
		window.clear();
		window.draw(tlo);
		window.draw(title);
		for (int i = 0;i < count;i++)
			window.draw(text[i]);
		window.display();
	}
}
void Game::options()
{
	Text title("Opcje gry", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	const int count = 4;
	Text text[count];
	string str[] = { "Resolution","800x600","1024x768","1600x900" };
	text[0].setFont(font);
	text[0].setCharacterSize(30);
	text[0].setString(str[0]);
	text[0].setPosition(300 - (text[0].getGlobalBounds().width / 2), 300);
	for (int i = 1;i < count; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(30);
		text[i].setString(str[i]);
		text[i].setPosition(500 - (text[i].getGlobalBounds().width / 2), (250 + i * 50));
	}
	while (state==OPTIONS)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = MENU;
			}
			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				Vector2u res(800, 600);
				setResolution(res);
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				Vector2u res(1024, 768);
				setResolution(res);
			}
			else if (text[3].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				Vector2u res(1600,900);
				setResolution(res);
			}
		}
		text[0].setFillColor(Color::Yellow);
		for (int i = 1;i < count;i++) {
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Green);
			else text[i].setFillColor(Color::Yellow);
		}
		window.clear();
		window.draw(tlo);
		window.draw(title);
		for (int i = 0; i < count;i++)
			window.draw(text[i]);
		window.display();
	}
}
void Game::game()
{
	Engine engine(window);
	state = MGAME;
}
void Game::load()
{
	Text title("Wczytaj", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	while (state == LOAD)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = MENU;
			}
		}
		window.clear();
		window.draw(tlo);
		window.draw(title);
		window.display();
	}
}
void Game::save()
{
	Text title("Zapisz", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	while (state == SAVE)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				state = MGAME;
			}
		}
		window.clear();
		window.draw(title);
		window.display();
	}
}
void Game::menuGame()
{
	Text title("Menu z gry", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	const int count = 3;
	Text text[count];
	string str[] = { "Save","Return","Exit" };
	for (int i = 0;i < count;i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(30);
		text[i].setString(str[i]);
		text[i].setPosition(100 - (text[i].getGlobalBounds().width / 2.5), (250 + i * 50));
	}
	while (state == MGAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GAME;
			}
			else if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = SAVE;
			}
			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = GAME;
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = MENU;
			}
		}
		for (int i = 0;i < count;i++) {
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Green);
			else text[i].setFillColor(Color::Yellow);
		}
		window.clear();
		window.draw(tlo);
		window.draw(title);
		for (int i = 0;i < count;i++)
			window.draw(text[i]);
		window.display();
	}
}