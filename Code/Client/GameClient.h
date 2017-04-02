#pragma once
#include <Game\Player.h>
#include <vector>
#include <memory>
#include <atomic>
#include <SFML\Graphics.hpp>
#include <Game\MoveState.h>

class ClientNetwork;

class GameClient
{
public:
	GameClient();
	~GameClient();
	void initialise();
	void input(sf::Event* _event); //Checks which key is pressed

private:
	std::atomic<MovementState> move_state = MovementState::Right; //Holds the current move state
	MovementState previous_state; //Holds the preivous move state
	std::unique_ptr<ClientNetwork> client_network = std::make_unique<ClientNetwork>();
	std::vector<Player*> players;
};