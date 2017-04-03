#include "GameClient.h"
#include "ClientNetwork.h"
#include <Game\MoveState.h>
#include <Game\PlayerManager.h>

GameClient::GameClient()
{
}

GameClient::~GameClient()
{
}

void GameClient::initialise()
{
	std::thread draw_thread(&GameClient::Draw, this);
	player_manager->initPlayer();
	client_network->client();
	Draw();
	draw_thread.join();
}

void GameClient::input(sf::Event* _event)
{
	/*Stores the previous movement state so that
	the player isn't sending unecessary packets
	of the same type to the server. */
	previous_state = move_state;

	//Sets the movement state based on WASD input
	switch (_event->key.code)
	{
	case sf::Keyboard::W:
		move_state = MovementState::Up;
		break;
	case sf::Keyboard::S:
		move_state = MovementState::Down;
		break;
	case sf::Keyboard::A:
		move_state = MovementState::Left;
		break;
	case sf::Keyboard::D:
		move_state = MovementState::Right;
		break;
	}

	/*If the preivous movestate isn't the
	current one then it's valid to be sent*/
	if (previous_state != move_state)
		client_network->sendInput(move_state);
}

void GameClient::Draw()
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
					input(&mainEvent);
				}
			}
			//Clear the game window
			window.clear();

			//for (auto& player : client->getPlayers())
			//{
			//	player.setPosition(sf::Vector2f(50, 50));
			//	window.draw(player.getSprite());
			//}

			//Draw the game window
			window.draw(player_manager->getPlayer()->getSprite());
			
			//client->draw(window);
			window.display();
		}
}
