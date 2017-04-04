#pragma once
#include <vector>
#include <memory>
#include <atomic>
#include <SFML\Graphics.hpp>
#include <Game\MoveState.h>
#include <Game\PlayerManager.h>

class ClientNetwork;
class Player;

class GameClient
{
public:
	GameClient();
	~GameClient();
	void initialise();
	void input(sf::Event* _event); //Checks which key is pressed
	void Draw();

private:
	std::atomic<MovementState> move_state = MovementState::NONE; //Holds the current move state
	MovementState previous_state; //Holds the preivous move state
	std::unique_ptr<ClientNetwork> client_network = std::make_unique<ClientNetwork>();
	std::unique_ptr<PlayerManager> player_manager = std::make_unique<PlayerManager>();
};