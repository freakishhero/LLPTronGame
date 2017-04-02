#include "GameClient.h"
#include "ClientNetwork.h"
#include <Game\MoveState.h>

void GameClient::initialise()
{
	//players.push_back(new Player("Pikachu.png"));
	//players[0]->setPosition(sf::Vector2f(50, 50));
	players.push_back(new Player("Pikachu.png"));
	client_network->client();
}

void GameClient::input(sf::Event* _event)
{
	/*Stores the previous movement state so that
	the player isn't sending unecessary packets
	of the same type to the server. */
	previous_state = move_state;

	//Sets the movement state based on WASD input
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

	/*If the preivous movestate isn't the
	current one then it's valid to be sent*/
	if (previous_state != move_state)
		client_network->sendInput(move_state);
}
