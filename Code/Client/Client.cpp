#include <SFML/Graphics.hpp>
#include <Game/MessageTypes.h>
#include "Client.h"

Client::Client(sf::Color _color, sf::Vector2f _size, sf::Vector2f _start_position)
{
	player.setSize(_size);
	player.setFillColor(_color);
	player.setOrigin(player.getSize() / 2.0f);
	player.setPosition(_start_position);
}

void Client::input(sf::Event* _event)
{
	if (_event->key.code = sf::Keyboard::W)
	{
		move_state = MovementState::Up;
	}
	else if (_event->key.code = sf::Keyboard::S)
	{
		move_state = MovementState::Down;
	}
	else if (_event->key.code = sf::Keyboard::A)
	{
		move_state = MovementState::Left;
	}
	else if (_event->key.code = sf::Keyboard::D)
	{
		move_state = MovementState::Right;
	}
		sendInput(move_state);
}

void Client::sendInput(MovementState _state)
{
	sf::Packet packet;

	packet << NetMsg::MOVEMENT << _state;
	socket.send(packet);
}

void Client::draw(sf::RenderWindow& _window)
{
	_window.draw(player);
}

void Client::client()
{
	TcpClient socket;
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
	if (status != sf::Socket::Done)
	{
		std::cout << "Error connecting to server:" << SERVER_IP << std::endl;
		return false;
	}

	std::cout << "Connected to server: " << SERVER_IP <<
		". on port: " << SERVER_TCP_PORT << "." << std::endl;
	_socket.setBlocking(false);
	return true;
}
