#pragma once
#include <vector>
#include "Player.h"
#include <SFML\Network.hpp>
#include <Game/MoveState.h>
class PlayerManager
{
public:

	friend sf::Packet& operator <<(sf::Packet& packet, const PlayerManager& playerManager);
	friend sf::Packet& operator >>(sf::Packet& packet, const PlayerManager& playerManager);

	std::vector<Player*> getPlayers();
	Player* getPlayer();
	void initPlayer(int client_count);
	void PlayerManager::input(sf::Event* _event);
	MovementState getMovementState();
protected:
	std::atomic<MovementState> move_state = MovementState::NONE; //Holds the current move state
	MovementState previous_state; //Holds the preivous move state
	std::vector<Player*> players;
	Player* player;
	int x = 0;
};