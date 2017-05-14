#include "Game.h"
#include <fstream>
void Game::setSound() {}
Texture Game::Set(Texture t)
{
	//ustawienie odpowiedniego tla
	if (window.getSize().x == 800) t.loadFromFile("Data/Graphic/1.png");
	else if (window.getSize().x == 1024) t.loadFromFile("Data/Graphic/2.png");
	else if (window.getSize().x == 1600) t.loadFromFile("Data/Graphic/3.png");
	return t;
}
void Game::setResolution(Vector2u x)
{
	//zmiana rozdzielczosci i zapisanie nowej do pliku
	fstream plik;
	plik.open("Data/config.cfg", ios::out | ios::trunc);
	plik << (int)x.x << " " << (int)x.y;
	plik.close();

	window.setSize(x);

	viewMenu.setSize(x.x, x.y);
	viewMenu.setCenter(x.x / 2, x.y / 2);

	viewGame.setSize(x.x, x.y);
	viewGame.setCenter(x.x / 2, x.y / 2);

	backgroundTexture = Set(backgroundTexture);
	background.setTexture(backgroundTexture);


}
void Game::checkConfig()
{
	//pobieranie zapisanej konfiguracji z pliku
	fstream plik;
	plik.open("Data/config.cfg", ios::in | ios::out);
	if (!plik.is_open())
	{
		MessageBox(NULL, "Config not found!", "ERROR", NULL);
		return;
	}

	cout << "Wczytano config" << endl;

	//pobieranie rozdzielczosci
	int x, y;
	plik >> x >> y;
	plik.close();

	//tworzenie okna i ustalanie rozdzielczosci
	window.create(VideoMode(x, y), "Gra", Style::Close);

	viewMenu.setSize(x, y);
	viewMenu.setCenter(x / 2, y / 2);

	viewGame.setSize(x, y);
	viewGame.setCenter(x / 2, y / 2);
	backgroundTexture = Set(backgroundTexture);
	background.setTexture(backgroundTexture);
}
Game::Game()
{	
	state = END;
	checkConfig();
	if (!font.loadFromFile("Data/roboto.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL); return;
	}
	state = MENU;
}
Game::~Game()
{

}
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
		case GameState::CHSELECTION:
			select();
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
		case GameState::EQUIPMENT:
			equipment();
			break;
		case GameState::FIGHT:
			fight();
			break;
		}
	}
}
void Game::menu()
{
	Text title("Gra", font, 80);
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
		text[i].setPosition(50.0, (250.0 + i * 50.0));
	}
	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyReleased
				&& event.key.code == Keyboard::Escape) {
				state = END;
			}
			else if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
				&& event.key.code == Mouse::Left)
			{
				state = CHSELECTION;
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
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Green);
			else text[i].setFillColor(Color::Yellow);
		}

		window.clear();
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		for (int i = 0;i < count;i++)
			window.draw(text[i]);
		window.display();
	}
}
void Game::options()
{
	Text title("Options", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	const int count = 4;
	Text text[count];
	string str[] = { "Resolution:","800x600","1024x768","1600x900" };
	for (int i = 0;i < count; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(30);
		text[i].setString(str[i]);
		text[i].setPosition(500.0 - (text[i].getGlobalBounds().width / 2.0), (250.0 + i * 50.0));
	}
	while (state == OPTIONS)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
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
				Vector2u res(1600, 900);
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
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < count;i++)
			window.draw(text[i]);
		window.display();
	}
}
void Game::select()
{
	Text title("Choose class", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	const int size = 4;
	Text text[size];
	string str[] = { "Exit","Warrior","Mage","Ranger" };
	text[0].setFont(font);
	text[0].setCharacterSize(30);
	text[0].setString(str[0]);
	text[0].setPosition(100 - (text[0].getGlobalBounds().width / 2), 700);
	for (int i = 1;i < size;i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(30);
		text[i].setString(str[i]);
		text[i].setPosition(50 + (i * 250) - text[i].getGlobalBounds().width / 2, 200);
	}
	while (state == CHSELECTION)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) || (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left))
				state = MENU;
			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				player = new Warrior();
				state = GAME;
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				player = new Mag();
				state = GAME;
			}
			else if (text[3].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				player = new Ranger();
				state = GAME;
			}
		}
		for (int i = 0;i < size;i++)
		{
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Green);
			else text[i].setFillColor(Color::Yellow);
		}
		window.clear();
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		for (int i = 0;i<size;i++)
			window.draw(text[i]);
		window.display();

	}
}
void Game::game()
{
	if (!continue_game_flag) {
		engine = new Engine(window, viewGame, font, *player);
		continue_game_flag = true;
	}
	string flag = engine->runEngine();
	if (flag == "menu")
		state = MGAME;
	else if (flag == "equipment")
		state = EQUIPMENT;
	else
		state = FIGHT;
}
void Game::load()
{
	Text title("Load Game", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	while (state == LOAD)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
			{
				state = MENU;
			}
		}
		window.clear();
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		window.display();
	}
}
void Game::save()
{
	Text title("Save game", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	while (state == SAVE)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
				state = MGAME;
			}
		}
		window.clear();
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		window.display();
	}
}
void Game::menuGame()
{
	Text title("Menu in game", font, 80);
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
		text[i].setPosition(100.0 - (text[i].getGlobalBounds().width / 2.5), (250.0 + i * 50.0));
	}
	while (state == MGAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
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
				continue_game_flag = false;
				state = MENU;
			}

		}
		for (int i = 0;i < count;i++) {
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Green);
			else text[i].setFillColor(Color::Yellow);
		}
		window.clear();
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		for (int i = 0;i < count;i++)
			window.draw(text[i]);
		window.display();
	}
}
void Game::equipment()
{
	Text title("Equipment", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 30);

	const int count = 6;
	string str[] = { "Class name ","Name ","Str ","Ag ", "Weapon ", "Armor " };
	Text text[count];

	text[0].setString(str[0] + player->getclassname());
	text[1].setString(str[1] + player->getname());
	text[2].setString(str[2] + to_string(player->getstr()));
	text[3].setString(str[3] + to_string(player->getag()));
	text[4].setString(str[4] + player->getcurrentweapon()->getName());
	text[5].setString(str[5] + player->getcurrentarmor()->getName());

	for (int i = 0;i < count;i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(15);
		text[i].setPosition(window.getSize().x / 2 - text[i].getGlobalBounds().width / 2,
			50 + title.getGlobalBounds().height + i * 15);
	}

	const int count_eq = player->getequipmentsize();
	Text *texteq = new Text[count_eq];
	int i = 0, j = 0;
	for (Item const& item : player->getequipment())
	{
		texteq[i + j].setFont(font);
		texteq[i + j].setCharacterSize(15);
		texteq[i + j].setString(item.getName());
		if (item.isweapon()) {
			texteq[i + j].setPosition(viewMenu.getCenter().x - 200,
				70 + count * 15 + title.getGlobalBounds().height + i * 15);
			i++;
		}
		else if (item.isarmor()) {
			texteq[i + j].setPosition(viewMenu.getCenter().x + 200,
				70 + count * 15 + title.getGlobalBounds().height + j * 15);
			j++;
		}
	}

	while (state == EQUIPMENT)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
			{
				state = GAME;
			}
			//jak wypisac ekwipunek z obsluga myszki
		}
		window.clear();
		window.setView(viewMenu);
		window.draw(background);
		window.draw(title);
		for (int i = 0;i<count;i++)
			window.draw(text[i]);
		for (int i = 0;i < count_eq;i++)
			window.draw(texteq[i]);
		window.display();
	}
	delete[] texteq;
}

void Game::fight()
{
	while (state == FIGHT) {
		if (!engine->action(viewMenu)) {
			state = GAME;
		}
	}
}
