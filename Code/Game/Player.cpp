#include <Game\Player.h>

Player::Player(std::string && fname)
{
	if (!player_texture.loadFromFile("..\\..\\Resources\\" + fname))
	{
		return;
	}
	player_sprite.setTexture(player_texture);
	player_sprite.setScale(sf::Vector2f(1, 1));
}

void Player::setPosition(sf::Vector2f _position)
{
	player_sprite.setPosition(_position);
}

void Player::movePosition(sf::Vector2f _position)
{
	position += _position;
}

sf::Vector2f Player::getPosition()
{
	return position;
}

void Player::updateRotation()
{
	switch (rotation)
	{
	case Rotation::LEFT:
		break;
	case Rotation::RIGHT:
		break;
	case Rotation::UP:
		break;
	case Rotation::DOWN:
		break;
	}
}

void Player::setRotation(Rotation _rotation)
{
	rotation = _rotation;
}

Rotation Player::getRotation()
{
	return rotation;
}

sf::Sprite Player::getSprite()
{
	return player_sprite;
}
