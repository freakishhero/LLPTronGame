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
	~Player() = default;
	void setPosition(sf::Vector2f _position);
	void movePosition(sf::Vector2f _position);
	void Draw(sf::RenderWindow& _window);
	sf::Sprite getSprite();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void masterMove();
private:
	std::atomic<int> moveInt;
	//std::thread movement;
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Texture player_texture;
	sf::Sprite player_sprite;
	float posX = 0.0f;
};