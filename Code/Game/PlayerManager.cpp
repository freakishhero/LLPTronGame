#include "PlayerManager.h"

std::vector<Player*> PlayerManager::getPlayers()
{
	return players;
}

void PlayerManager::initPlayer(int client_count)
{	
	switch (client_count)
	{
	default:
		break;
	case 1:
		player = new Player("Pikachu.png");
		break;
	case 2:
		player = new Player("Bulbasaur.png");
		break;
	case 3:
		player = new Player("Squirtle.png");
		break;
	case 4:
		player = new Player("Charmander.png");
		break;
	}
	players.push_back(player);
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