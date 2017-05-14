#include "NPC.h"

void NPC::setMonster(int height,int width,Level& level) {
	srand(time(NULL));
	NPCMap.resize(height);
	for (int y = 0;y < width;y++)
		NPCMap[y].resize(width);

	for (int i = 0;i < height;i++) {
		for (int j = 0;j < width;j++) {
			NPCMap[j][i].type = DEFAULT;
		}
	}
	NPCMap[10][10] = getNPC(0);
	NPCMap[11][11] = getNPC(2);
	int i = 0;
	while (i<30) {
		int x = rand() % height + 0;
		int y = rand() % width + 0;
		if (x != level.startX && y != level.startY) {
			if ((!level.map[y][x].collideable && level.map[y][x].interactable) &&
				(NPCMap[y][x].type != TRADER || NPCMap[y][x].type != BOSS)) {
				float c = (rand() % 101 + 0) / 100;
				if (c >= 1 - level.map[y][x].chance) {
					NPCMap[y][x] = getNPC(1);
					i++;
				}
			}
		}
	}
}
NPC::Npc NPC::getNPC(short code) {
	Npc npcc;
	npcc.type = NPCType(code);
	switch (NPCType(code))
	{
	case NPC::MONSTER:
		npcc.interactable = true;
		npcc.exist = true;
		break;
	case NPC::TRADER:
		npcc.interactable = true;
		npcc.exist = true;
		break;
	case NPC::BOSS:
		npcc.interactable = true;
		npcc.exist = true;
		break;
	default:
		npcc.interactable = false;
		npcc.exist = false;
		break;


	}
	return npcc;
}
int NPC::check(Vector2i position) {
	if (NPCMap[position.y][position.x].type == TRADER) return 0;
	if (NPCMap[position.y][position.x].type == MONSTER) return 1;
	if (NPCMap[position.y][position.x].type == BOSS) return 2;
}
bool Trader::action(RenderWindow* window,View* view, Font font,Player*, bool typ) {
	Text title("Trade",font,50);
	title.setPosition(view->getCenter().x - (view->getSize().x / 2.5), view->getCenter().y - (view->getSize().y / 2.5) );
	Event event;
	Vector2f mouse(Mouse::getPosition(*window));
	while (window->pollEvent(event)) {
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
			return false;
		}
	}
	window->clear();
	window->draw(title);
	window->display();
}
bool Monster::action(RenderWindow* window, View* view, Font font, Player* player,bool typ) {
	unsigned hp = gethp();
	bool yourTurn = true;
	string str[] = { "Zwyk³y","Szybki atak","twoje hp","pzeciwnika hp" };
	Text text[4];
	for (unsigned i = 0;i < 4;i++) {
		text[i].setFont(font);
		text[i].setCharacterSize(40);
		text[i].setString(str[i]);
		text[i].setPosition(150.0, (250.0 + i * 50.0));
	}
	Text title("FIGHT", font, 50);
	title.setPosition(window->getSize().x / 2 - title.getGlobalBounds().width / 2, 30);
	while (true) {
		Vector2f mouse(Mouse::getPosition(*window));
		Event event;
		while (window->pollEvent(event)) {
			if (hp == 0) {
				typ = 1;
				return true;
			} // pokonany
			if (player->gethp() == 0) {
				typ = 0;
				return true;
			} // nie pokonany
			text[2].setString(str[2] + to_string(player->gethp()));
			text[3].setString(str[3] + to_string(hp));
			if (yourTurn) {
				if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
					&& event.key.code == Mouse::Left) {
					hp -= 10;
					yourTurn = false;
				}
				else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
					&& event.key.code == Mouse::Left) {
					hp -= 5;
					yourTurn = false;
				}
			}
			else {
				player->sethp(player->gethp() - rand() % 10 + 0);
				yourTurn = true;
			}
			for (unsigned i = 0;i < 2;i++) {
				if (text[i].getGlobalBounds().contains(mouse))
					text[i].setFillColor(Color::Blue);
				else text[i].setFillColor(Color::Red);
			}
			window->clear(Color::Black);
			window->setView(*view);
			window->draw(title);
			for (unsigned i = 0;i < 4;i++)
				window->draw(text[i]);
			window->display();
		}
	}
	return false;
}
bool Boss::action(RenderWindow* window,View* view, Font font,Player*, bool typ) {
	Text title("DIE", font, 50);
	title.setPosition(view->getCenter().x - (view->getSize().x / 2.5), view->getCenter().y - (view->getSize().y / 2.5));
	Event event;
	Vector2f mouse(Mouse::getPosition(*window));
	while (window->pollEvent(event)) {
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
			return false;
		}
	}
	window->clear();
	window->draw(title);
	window->display();
}