#include "PlayerManager.h"
#include <Client\ClientNetwork.h>
std::vector<Player*> PlayerManager::getPlayers()
{
	return players;
}

void PlayerManager::initPlayer(int client_count)
{	
	if (client_count == 1)
	{
		for (auto& player : players)
		{
			player->KillThread();
		}
		//init player 1 singleplayer
		players.clear();
		player = new Player("Pikachu.png");
		players.push_back(player);
		getPlayers()[0]->setPosition(sf::Vector2f(25.0f, 25.0f));
		getPlayers()[0]->setPlayerID(1);
		getPlayers()[0]->getCollider()->setFillColor(sf::Color::Yellow);
		getPlayers()[0]->getCollider()->setPosition(getPlayers()[0]->getSprite().getPosition().x + 45.0f, getPlayers()[0]->getSprite().getPosition().y + 60.0f);
	}
	if (client_count == 2)
	{
		for (auto& player : players)
		{
			player->KillThread();
		}
		//init player 1
		players.clear();
		player = new Player("Pikachu.png");
		players.push_back(player);
		getPlayers()[0]->setPosition(sf::Vector2f(25.0f, 25.0f));
		getPlayers()[0]->setPlayerID(1);
		getPlayers()[0]->getCollider()->setFillColor(sf::Color::Yellow);
		getPlayers()[0]->getCollider()->setSize(sf::Vector2f(0.01f, 0.01f));
		getPlayers()[0]->getCollider()->setPosition(getPlayers()[0]->getSprite().getPosition().x + 45.0f, getPlayers()[0]->getSprite().getPosition().y + 60.0f);

		// init player 2
		player = new Player("Bulbasaur.png");
		players.push_back(player);
		getPlayers()[1]->setPosition(sf::Vector2f(400.0f, 25.0f));
		getPlayers()[1]->setPlayerID(2);
		getPlayers()[1]->getCollider()->setFillColor(sf::Color::Green);
		getPlayers()[0]->getCollider()->setSize(sf::Vector2f(0.01f, 0.01f));
		getPlayers()[0]->getCollider()->setPosition(getPlayers()[0]->getSprite().getPosition().x + 45.0f, getPlayers()[0]->getSprite().getPosition().y + 60.0f);
	}
}
Player * PlayerManager::getPlayer()
{
	return player;
}


sf::Packet& operator<<(sf::Packet& packet,  PlayerManager& playerManager)
{
	//packet << playerManager.getPlayers;
	return packet;
}

sf::Packet& operator >> (sf::Packet& packet,  PlayerManager& playerManager)
{
//	packet >> playerManager.getPlayers;
	return packet;
}

void PlayerManager::input(sf::Event* _event)
{
	/*Stores the previous movement state so that
	the player isn't sending unecessary packets
	of the same type to the server. */
	previous_state = move_state;

	//Sets the movement state based on WASD input
	//if (player->getPlayerNum() == 1)
	//{
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

		//Sets the movement state based on arrow key input
		//if (player->getPlayerNum() == 2)
		switch (_event->key.code)
			{
			case sf::Keyboard::Up:
				move_state = MovementState::Up2;
				break;
			case sf::Keyboard::Down:
				move_state = MovementState::Down2;
				break;
			case sf::Keyboard::Left:
				move_state = MovementState::Left2;
				break;
			case sf::Keyboard::Right:
				move_state = MovementState::Right2;
				break;
			}
}

MovementState PlayerManager::getMovementState()
{
	return move_state;
}
