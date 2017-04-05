#pragma once
#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <SFML\Network.hpp>
#include <SFML\System.hpp>

#include "Client.h"
#include <Game\MessageTypes.h>
#include <Game\Player.h>
#include <functional>

constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

using TcpClient = sf::TcpSocket;
using TcpClientPtr = std::unique_ptr<TcpClient>;
using TcpClients = std::vector<Client>;

class PlayerManager;

class Server {

	
// prototypes
public:

	Server();
	~Server() = default;

	bool bindServerPort(sf::TcpListener&);
	void clearStaleCli(TcpClients & tcp_clients);
	void connect(sf::TcpListener& tcp_listener, sf::SocketSelector& selector, TcpClients& tcp_clients);
	void listen(sf::TcpListener&, sf::SocketSelector&, TcpClients&);
	void processPlayerMovement(sf::Packet &packet, Client & sender, TcpClients & tcp_clients);
	void ping(TcpClients& tcp_clients);
	void receiveMsg(TcpClients& tcp_clients, sf::SocketSelector& selector);
	void runServer();

private:
	//std::vector<PlayerManager*> players;
	PacketType packet_type;
};