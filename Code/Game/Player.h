#pragma once
#include <string>

#include <SFML\Graphics.hpp>
#include "Rotation.h"

class Player : public sf::Sprite
{
public:
	Player(std::string&&);
	~Player() = default;
	void setPosition(sf::Vector2f _position);
	void movePosition(sf::Vector2f _position);
	sf::Vector2f getPosition();
	void updateRotation();
	void setRotation(Rotation _rotation);
	Rotation getRotation();
	sf::Sprite getSprite();

private:
	sf::Vector2f position = sf::Vector2f(0, 0);
	Rotation rotation = Rotation::LEFT;
	sf::Texture player_texture;
	sf::Sprite player_sprite;
};