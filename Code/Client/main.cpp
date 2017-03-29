#include <SFML/Graphics.hpp>
#include "Client.h"

std::unique_ptr<Client> client = std::make_unique<Client>(sf::Color::Red, sf::Vector2f(50.0f, 50.0f),  sf::Vector2f(25.0f, 25.0f));

void draw()
{
	//Creates the client window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TRONSEXUAL!", sf::Style::Close);
	//window.setSize(sf::Vector2u(1440, 900));

	while (window.isOpen())
	{
		sf::Event mainEvent;

		while (window.pollEvent(mainEvent))
		{
			if (mainEvent.type = sf::Event::Closed)
			{
				window.close();
			}
			if (mainEvent.type = sf::Event::KeyPressed)
			{
				switch (mainEvent.key.code)
				{
					client->input(&mainEvent);
				}
			}
		}

		window.clear();
		client->draw(window);
		window.display();
	}
}

int main()
{
	sf::Thread thread(&draw);
	thread.launch();

	client->client();
		return 0;
}