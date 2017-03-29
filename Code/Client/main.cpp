#include <SFML/Graphics.hpp>
#include "Client.h"

std::unique_ptr<Client> client = std::make_unique<Client>(sf::Color::Red, sf::Vector2f(50.0f, 50.0f),  sf::Vector2f(25.0f, 25.0f));
float deltaTime = 0.0f;
sf::Clock dtClock;

void draw()
{
	//Creates the client window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TRON!", sf::Style::Close);
	//window.setSize(sf::Vector2u(1440, 900));

	while (window.isOpen())
	{
		deltaTime = dtClock.restart().asSeconds();
		sf::Event mainEvent;

		while (window.pollEvent(mainEvent))
		{
			switch (mainEvent.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.close();
				break;
			}
		}
		
		client->update(deltaTime);

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