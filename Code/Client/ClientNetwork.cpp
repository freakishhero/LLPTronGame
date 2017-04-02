#include <SFML/Graphics.hpp>
#include <Game/MessageTypes.h>
#include "ClientNetwork.h"

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

void ClientNetwork::draw(sf::RenderWindow& _window)
{
	//Draws the player to the window
	//_window.draw(player);
}

void ClientNetwork::disconnect()
{
	sf::Packet packet;

	packet << sf::Socket::Disconnected;
	socket.send(packet);
}

void ClientNetwork::client()
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
			if (status == sf::Socket::Done)
			{
				float meme = 0.0f;
				int header = 0;

				packet >> header;

				PacketType packet_type = static_cast<PacketType>(header);
				if (packet_type == PacketType::MOVEMENT)
				{
					//packet >> meme;
					//player.setPosition(sf::Vector2f(meme, 300.0f));
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