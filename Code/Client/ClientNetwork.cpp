#include <SFML/Graphics.hpp>
#include <Game/MessageTypes.h>
#include "ClientNetwork.h"

ClientNetwork::ClientNetwork()
{
	std::thread movement(&ClientNetwork::movementListener, this);
	movement.detach();
}

ClientNetwork::~ClientNetwork()
{
}

void ClientNetwork::sendInput(MovementState _state)
{
	//Creates a packet
	sf::Packet packet;

	/* Adds the packet type and movement state
	to the packet*/
	packet << PacketType::MOVEMENT << _state;

	//Sends the packet
	socket.send(packet);
}

void ClientNetwork::disconnect()
{
	sf::Packet packet;

	packet << sf::Socket::Disconnected;
	socket.send(packet);
}

void ClientNetwork::movementListener()
{
	/*while (true)
	{
	}*/
}

void ClientNetwork::client(std::unique_ptr<PlayerManager>& _manager)
{
	//Checks if the player can connect
	if (!connect(socket))
	{
		return;
	}
	sf::Packet packet;
	packet << PacketType::CLIENT_COUNT;
	socket.send(packet);
	//managerHeader = _manager;
	auto handle = std::async(std::launch::async, [&]
	{		//keep track of the socket status
		sf::Socket::Status status;

		do
		{
			sf::Packet packet;
			status = socket.receive(packet);
			if (status == sf::Socket::Done)
			{
				int header = 0;
				//int move_state;

				packet >> header;

				PacketType packet_type = static_cast<PacketType>(header);

				if (packet_type == PacketType::CLIENT_COUNT)
				{
					/*if (counter > 0)
					*///{
					int player_count = 0;
					packet >> player_count;
					_manager->initPlayer(player_count);
				}
				//counter++;
				//}



				if (packet_type == PacketType::MOVEMENT)
				{
					int move_state;
					packet >> move_state;
					//move_state = movestate;
					if (move_state == 0)
					{
						_manager->getPlayers()[0]->movePlayer(0);
					}
					else if (move_state == 1)
					{
						_manager->getPlayers()[0]->movePlayer(1);
					}
					else if (move_state == 2)
					{
						_manager->getPlayers()[0]->movePlayer(2);
					}
					else if (move_state == 3)
					{
						_manager->getPlayers()[0]->movePlayer(3);
					}


					if (move_state == 4)
					{
						if (_manager->getPlayers().size() == 2)
							_manager->getPlayers()[1]->movePlayer(0);
					}
					else if (move_state == 5)
					{
						if (_manager->getPlayers().size() == 2)
							_manager->getPlayers()[1]->movePlayer(1);
					}
					else if (move_state == 6)
					{
						if (_manager->getPlayers().size() == 2)
							_manager->getPlayers()[1]->movePlayer(2);
					}
					else if (move_state == 7)
					{
						if (_manager->getPlayers().size() == 2)
							_manager->getPlayers()[1]->movePlayer(3);
					}
				}
				else if (packet_type == PacketType::NEW_CLIENT)
				{
					int new_player;
					packet >> new_player;
					if (client_count != 1 || client_count != 2)
					{
						client_count = new_player;
					}
					_manager->initPlayer(new_player);

				}
				else if (packet_type == PacketType::PONG)
				{
				}
			}
		} while (status != sf::Socket::Disconnected);

	});
}

bool ClientNetwork::connect(TcpClient& _socket)
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
