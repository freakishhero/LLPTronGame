#include <SFML/Graphics.hpp>
#include <Game/MessageTypes.h>
#include "Client.h"

Client::Client(sf::Color _color, sf::Vector2f _size, sf::Vector2f _start_position)
{
	//creates the player
	player.setSize(_size);
	player.setFillColor(_color);
	player.setOrigin(player.getSize() / 2.0f);
	player.setPosition(_start_position);
}

void Client::input(sf::Event* _event)
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
	if(previous_state != move_state)
		sendInput(move_state);
}

void Client::sendInput(MovementState _state)
{
	//Creates a packet
	sf::Packet packet;

	/* Adds the packet type and movement state
	   to the packet*/
	packet << PacketType::MOVEMENT << _state;

	//Sends the packet
	socket.send(packet);
}

void Client::draw(sf::RenderWindow& _window)
{
	//Draws the player to the window
	_window.draw(player);
}

void Client::client()
{
	//Checks if the player can connect
	if (!connect(socket))
	{
		return;
	}

	auto handle = std::async(std::launch::async, [&]
	{		//keep track of the socket status
		sf::Socket::Status status;
	
		do
		{
			sf::Packet packet;
			status = socket.receive(packet);
			if ( status == sf::Socket::Done )
			{
				int header = 0;
				packet >> header;
			}
		} while (status != sf::Socket::Disconnected);

	});
}

bool Client::connect(TcpClient& _socket)
{
	auto status = _socket.connect(SERVER_IP, SERVER_TCP_PORT);

	//If the player failed to connect
	if (status != sf::Socket::Done)
	{
		std::cout << "Error connecting to server:" << SERVER_IP << std::endl;
		return false;
	}

	//If the player managed to connect
	std::cout << "Connected to server: " << SERVER_IP <<
		". on port: " << SERVER_TCP_PORT << "." << std::endl;
	_socket.setBlocking(false);
	return true;
}
