#include <SFML/Graphics.hpp>
#include "Client.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
		}
		client->client();
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}