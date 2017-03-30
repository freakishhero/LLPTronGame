#pragma once
#include <SFML/Network.hpp>
#include <future>
#include <iostream>
#include <string>
#include <Game/MoveState.h>

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

	void client(); //Connects to the server
	bool connect(TcpClient&); //Validates connection
	void input(sf::Event* _event); //Checks which key is pressed
	void sendInput(MovementState _state); //Sends a packet based on key press
	void draw(sf::RenderWindow& _window); //Draws the player

private:
	TcpClient socket; // Socket for the client
	sf::RectangleShape player;	//Creates a shape for the player
	std::atomic<MovementState> move_state = MovementState::Right; //Holds the current move state
	MovementState previous_state; //Holds the preivous move state
};