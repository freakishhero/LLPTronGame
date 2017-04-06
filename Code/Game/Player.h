#pragma once
#include <string>

#include <SFML\Graphics.hpp>
#include "Rotation.h"
#include <thread>
#include <atomic>
class Player : public sf::Sprite
{
public:
	Player(std::string&&);
	~Player();

	sf::Sprite getSprite();

	void Draw(sf::RenderWindow& _window);

	void movePlayer(int _direction);
	void updateMovement();

	void setPlayerID(int ID);
	int getPlayerID();

	void KillThread();

	sf::RectangleShape* getCollider();

private:
	int playerID = 0;
	bool ThreadAlive = true;
	std::atomic<int> movement_direction;
	sf::Texture player_texture;
	sf::Sprite player_sprite;
	sf::RectangleShape collider;
};