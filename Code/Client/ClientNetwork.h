#pragma once
#include <SFML/Network.hpp>
#include <future>
#include <iostream>
#include <string>
#include <memory>
#include <Game/MoveState.h>
#include <Game\PlayerManager.h>
#include <thread>
#include <atomic>
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

	void client(std::unique_ptr<PlayerManager>& _manager); //Connects to the server
	bool connect(TcpClient&); //Validates connection
	void sendInput(MovementState _state); //Sends a packet based on key press
	void disconnect();
	void movementListener();
	//void playerMove(int direction, std::unique_ptr<PlayerManager>& _manager);
private:
	//std::unique_ptr<PlayerManager>& managerHeader;
	//std::atomic<int> move_state;
//	int move_state;
	int amountOfClients;
	std::thread movement;
	TcpClient socket; // Socket for the client
	int counter = 0;
	
};