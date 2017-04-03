#pragma once
#include <SFML/Network.hpp>
#include <future>
#include <iostream>
#include <string>
#include <Game/MoveState.h>
#include <Game\PlayerManager.h>

using TcpClient = sf::TcpSocket;
using TcpClientPtr = std::unique_ptr<TcpClient>;
using TcpClients = std::vector<TcpClientPtr>;

const sf::IpAddress SERVER_IP("127.0.0.1");
constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

class ClientNetwork
{
public:
	ClientNetwork();
	~ClientNetwork();

	void client(); //Connects to the server
	bool connect(TcpClient&); //Validates connection
	void sendInput(MovementState _state); //Sends a packet based on key press
	void disconnect();

private:
	TcpClient socket; // Socket for the client
	std::shared_ptr<PlayerManager> player_manager = std::make_unique<PlayerManager>();
};