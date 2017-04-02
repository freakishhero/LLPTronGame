#include <SFML/Graphics.hpp>
#include "ClientNetwork.h"
#include "GameClient.h"
#include <Game\Player.h>

std::unique_ptr<GameClient> client = std::make_unique<GameClient>();

void draw()
{
	//Creates the client window
	sf::RenderWindow window(sf::VideoMode(800, 600), "POKéTRON!", sf::Style::Close);

	while (window.isOpen())
	{
		//creates game event
		sf::Event mainEvent;

		while (window.pollEvent(mainEvent))
		{
			//If the window is closed
			if (mainEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			//If a ke is pressed in the window
			if (mainEvent.type == sf::Event::KeyPressed)
			{
				//Send the event to the client input
				client->input(&mainEvent);
			}
		}

		//Clear the game window
		window.clear();

		//Draw the game window
		//client->draw(window);
		window.display();
	}
}

int main()
{
	/* Creates a thread of the draw function so it can run
		with other tasks instead of halting the game. */
	sf::Thread draw_thread(&draw);

		//Runs the draw thread
	draw_thread.launch();

		/* connects to the server */
	client->initialise();
		return 0;
}