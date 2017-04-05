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
		for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); i++)
		{
			(*i)->KillThread();
		}
		players.clear();
		player = new Player("Pikachu.png");
		players.push_back(player);
		getPlayers()[0]->setPosition(sf::Vector2f(25.0f, 25.0f));
		getPlayers()[0]->setPlayerNum(1);
	}
	if (client_count == 2)
	{
		for (std::vector<Player*>::iterator i = players.begin(); i != players.end(); i++)
		{
			(*i)->KillThread();
		}
		players.clear();
		player = new Player("Pikachu.png");
		players.push_back(player);
		getPlayers()[0]->setPosition(sf::Vector2f(25.0f, 25.0f));
		getPlayers()[0]->setPlayerNum(1);
		player = new Player("Bulbasaur.png");
		players.push_back(player);
		getPlayers()[1]->setPosition(sf::Vector2f(400.0f, 25.0f));
		getPlayers()[1]->setPlayerNum(2);
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
	//}


	//if (player->getPlayerNum() == 2)
	//{
		switch (_event->key.code)
			{
			case sf::Keyboard::T:
				move_state = MovementState::Up2;
				break;
			case sf::Keyboard::G:
				move_state = MovementState::Down2;
				break;
			case sf::Keyboard::F:
				move_state = MovementState::Left2;
				break;
			case sf::Keyboard::H:
				move_state = MovementState::Right2;
				break;
			}
	//}
	
	/*If the preivous movestate isn't the
	current one then it's valid to be sent*/
	if (previous_state != move_state)
	{

	}
}

MovementState PlayerManager::getMovementState()
{
	return move_state;
}
