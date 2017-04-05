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
	//std::unique_ptr<PlayerManager> player_manager(new PlayerManager());
	std::thread draw_thread(&GameClient::Draw, this);
	client_network->client(player_manager);
	Draw();
	draw_thread.join();
}

void GameClient::input(sf::Event* _event)
{
	/*Stores the previous movement state so that
	the player isn't sending unecessary packets
	of the same type to the server. */
	previous_state = move_state;
	player_manager->input(_event);
	move_state = player_manager->getMovementState();
	/*If the preivous movestate isn't the
	current one then it's valid to be sent*/
	if (previous_state != move_state)
		client_network->sendInput(player_manager->getMovementState());
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
				//If a key is pressed in the window
				if (mainEvent.type == sf::Event::KeyPressed)
				{
					//Send the event to the player manager
					this->input(&mainEvent);
					
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
			//window.draw(player_manager->getPlayer()->getSprite());
			for (auto& player : player_manager->getPlayers())
			{
				player->Draw(window);
			}
			//player_manager->getPlayer()->Draw(window);
			//client->draw(window);
			window.display();
		}
}
