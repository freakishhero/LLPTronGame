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
	void input(sf::Event* _event);
	void sendInput(MovementState _state);

	void draw(sf::RenderWindow& _window);

private:
	sf::TcpSocket socket;
	sf::RectangleShape player;
	float movement_speed = 250.0f;
	MovementState move_state = MovementState::Right;
};