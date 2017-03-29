#include <SFML/Graphics.hpp>
#include "Client.h"

Client::Client(sf::Color _color, sf::Vector2f _size, sf::Vector2f _start_position)
{
	m_player.setSize(_size);
	m_player.setFillColor(_color);
	m_player.setOrigin(m_player.getSize() / 2.0f);
	m_player.setPosition(_start_position);
}

void Client::input(TcpClient& _socket)
{
	while (true)
	{
		char input = 'a';
		sf::Packet packet;
		packet << input;
		//packet << NetMsg::CHAT << input;
		_socket.send(packet);
	}
}

void Client::draw(sf::RenderWindow& _window)
{
	_window.draw(m_player);
}

void Client::update(float _dt)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_move_state = MovementState::Left;
	}
	else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_move_state = MovementState::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_move_state = MovementState::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_move_state = MovementState::Down;
	}

	switch (m_move_state)
	{
	case MovementState::Left:
		movement.x -= m_movement_speed * _dt;
		break;
	case MovementState::Right:
		movement.x += m_movement_speed * _dt;
		break;
	case MovementState::Up:
		movement.y -= m_movement_speed * _dt;
		break;
	case MovementState::Down:
		movement.y += m_movement_speed * _dt;
		break;
	}

	m_player.move(movement);
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

	return input(socket);
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
