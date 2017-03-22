#include <SFML/Graphics.hpp>
#include "Client.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Event::Resized);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	std::unique_ptr<Client> client = std::make_unique<Client>();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized);
		}
		window.clear();
		window.draw(shape);
		window.display();
		client->client();
	}

	return 0;
}