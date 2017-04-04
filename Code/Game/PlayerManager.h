#pragma once
#include <vector>
#include "Player.h"
#include <SFML\Network.hpp>

class PlayerManager
{
public:

	friend sf::Packet& operator <<(sf::Packet& packet, const PlayerManager& playerManager);
	friend sf::Packet& operator >>(sf::Packet& packet, const PlayerManager& playerManager);

	std::vector<Player*> getPlayers();
	Player* getPlayer();
	void initPlayer(int client_count);
protected:
	std::vector<Player*> players;
	Player* player;
	int x = 0;
};