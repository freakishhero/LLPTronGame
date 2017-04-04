#pragma once
#include <SFML/Network.hpp>
enum PacketType : sf::Int32
{
	INVALID = 0,
	MOVEMENT = 1,
	PING = 2,
	PONG = 3,
	CLIENT_COUNT = 4,
	NEW_CLIENT = 5
};