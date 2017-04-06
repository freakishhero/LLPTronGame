#include "GameClient.h"
#include "ClientNetwork.h"
#include <Game\MoveState.h>
#include <Game\PlayerManager.h>
#include <SFML\Audio.hpp>

GameClient::GameClient()
{
}

GameClient::~GameClient()
{
}

void GameClient::initialise()
{
	if (!background_texture.loadFromFile("..\\..\\Resources\\Background.png"))
	{
		return;
	}
	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(0, 0);

	if (!start.openFromFile("..\\..\\resources\\PokemonOut.ogg"))
	{
		return;
	}
	if (!theme.openFromFile("..\\..\\Resources\\Theme.ogg"))
	{
		return;
	}
	start.play();
	theme.play();
	createGrid();
	//std::unique_ptr<PlayerManager> player_manager(new PlayerManager());
	std::thread draw_thread(&GameClient::Draw, this);
	client_network->client(player_manager);
	//Draw();
	draw_thread.join();
}

void GameClient::createGrid()
{
	trail.reserve(900);

	int x = 0;
	int y = 0;

	//for (int i = 0; i < 2025; i++)
	for (int i = 0; i < 8100; i++)
	{
		trail.push_back(sf::RectangleShape());

		trail[i].setFillColor(sf::Color::Transparent);
		trail[i].setSize(sf::Vector2f(10, 10));
		trail[i].setPosition((i % 90) * 10, (i / 90) * 10);


		//LGBTQ GRID kinda
		//trail[i].setPosition((i % 45) * 20, (i / 45) * 20);
		//if(i >= 0 && i < 405)
		//	trail[i].setFillColor(sf::Color::Yellow);
		//if (i >= 405 && i < 810)
		//	trail[i].setFillColor(sf::Color::Red);
		//if (i >= 810 && i < 1215)
		//	trail[i].setFillColor(sf::Color::Green);
		//if (i >= 1215 && i < 1620)
		//	trail[i].setFillColor(sf::Color::Blue);
		//if (i >= 1620 && i < 2025)
		//	trail[i].setFillColor(sf::Color::Cyan);
	}
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
	sf::RenderWindow window(sf::VideoMode(900, 900), "POKéTRON!", sf::Style::Close);

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
		window.draw(background_sprite);
		//for (auto& player : client->getPlayers())
		//{
		//	player.setPosition(sf::Vector2f(50, 50));
		//	window.draw(player.getSprite());
		//}

		//Draw the game window
		//window.draw(player_manager->getPlayer()->getSprite());

		/*for (auto& tile : trail)
		{
		if (hi.getGlobalBounds().intersects(tile.getGlobalBounds()))
		{
		tile.setFillColor(hi.getFillColor());
		}
		}*/


		//for (auto& tile : trail)
		//{
		//	window.draw(tile);
		//}

		for (auto& player : player_manager->getPlayers())
		{

			for (int i = 0; i < trail.size(); i++)
			{
				
				if (player->getCollider()->getGlobalBounds().intersects(trail[i].getGlobalBounds()))
				{
					if (i != last_index_collided)
					{
						if (trail[i].getFillColor() == sf::Color::Transparent)
						{
							trail[i].setFillColor(player->getCollider()->getFillColor());
							last_index_collided = i;
						}
						else if (trail[i].getFillColor() != sf::Color::Transparent)
						{
						window.close();
						}
					}
					
				}
				window.draw(trail[i]);
				/* Add colided tiles to a vector and only render those*/
			}
			player->getCollider()->setPosition(player->getSprite().getPosition().x + 45.0f, player->getSprite().getPosition().y + 60.0f);
			player->Draw(window);
			
		}
		//player_manager->getPlayer()->Draw(window);
		//client->draw(window);
		window.display();
	}
}
