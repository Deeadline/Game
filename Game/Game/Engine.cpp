#include "Engine.h"

Engine::Engine(RenderWindow &win)
{
	runEngine(win);
}
Engine::~Engine() {}
void Engine::runEngine(RenderWindow &window)
{
	bool menu = false;
	while (!menu)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
				menu = true;
			if (event.type == Event::KeyPressed)
			{
				if(event.key.code == Keyboard::W)
				player.idz(mouse);
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::W)
					player.stop();
			}
		}
		player.update(mouse);
		window.clear();
		window.draw(player);
		window.display();
	}
}