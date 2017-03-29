#pragma once
#include <SFML/Network.hpp>
#include <future>
#include <iostream>
#include <string>
#include "MoveState.h"

using TcpClient = sf::TcpSocket;
using TcpClientPtr = std::unique_ptr<TcpClient>;
using TcpClients = std::vector<TcpClientPtr>;

const sf::IpAddress SERVER_IP("127.0.0.1");
constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

class Client
{
public:
	Client(sf::Color _color, sf::Vector2f _size, sf::Vector2f _start_position);
	~Client() = default;

	void client();
	bool connect(TcpClient&);
	void input(TcpClient& _socket);

	void draw(sf::RenderWindow& _window);
	void update(float _dt);

private:
	sf::RectangleShape m_player;
	float m_movement_speed = 250.0f;
	MovementState m_move_state = MovementState::Right;
};