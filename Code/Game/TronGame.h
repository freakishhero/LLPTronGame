#pragma once
#include "Player.h"
namespace sf {
	class Packet;
}

class TronGame
{
public:
	TronGame() = default;
	~TronGame() = default;

	std::vector<Player> players;

	friend sf::Packet& operator <<(sf::Packet& packet, const TronGame& game);
	friend sf::Packet& operator >>(sf::Packet& packet, const TronGame& game);
};