#include <SFML/Graphics.hpp>
#include "Client.h"

void draw()
{
	sf::CircleShape shape(100.f);
	sf::RenderWindow window(sf::VideoMode(800, 600), "TRON!"/*, sf::Event::Resized*/);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//else if (event.type == sf::Event::Resized);
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
}
int main()
{
	std::unique_ptr<Client> client = std::make_unique<Client>();
	sf::Thread thread(&draw);
	thread.launch();

	client->client();
		return 0;
}