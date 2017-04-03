#pragma once
#include <vector>
#include "Player.h"

class PlayerManager
{
public:
	std::vector<Player*> getPlayers();
	Player* getPlayer();
	void initPlayer();
private:
	std::vector<Player*> players;
	Player* player;
};