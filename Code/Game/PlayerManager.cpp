#include "PlayerManager.h"

std::vector<Player*> PlayerManager::getPlayers()
{
	return players;
}

Player * PlayerManager::getPlayer()
{
	return player;
}

void PlayerManager::initPlayer()
{
	player = new Player("Pikachu.png");
}
