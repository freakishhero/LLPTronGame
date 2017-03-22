#include "Client.h"

void Client::input(TcpClient & socket)
{
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);

		sf::Packet packet;
		//packet << NetMsg::CHAT << input;
		socket.send(packet);
	}
}

void Client::client()
{
	TcpClient socket;
	if (!connect(socket))
	{
		return;
	}

	auto handle = std::async(std::launch::async, [&]
	
	{		// keep track of the socket status
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

	//return input(socket);
}

bool Client::connect(TcpClient& socket)
{
	auto status = socket.connect(SERVER_IP, SERVER_TCP_PORT);
	if (status != sf::Socket::Done)
	{
		std::cout << "Error connecting to server:" << SERVER_IP << std::endl;
		return false;
	}

	std::cout << "Connected to server: " << SERVER_IP << std::endl;
	socket.setBlocking(false);
	return true;
}
