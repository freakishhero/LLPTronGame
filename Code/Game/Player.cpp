#include <Game\Player.h>

Player::Player(std::string && fname)
{
	std::thread movement(&Player::masterMove, this);
	movement.detach();
	if (!player_texture.loadFromFile("..\\..\\Resources\\" + fname))
	{
		return;
	}
	player_sprite.setTexture(player_texture);
	player_sprite.setScale(sf::Vector2f(1, 1));
}

//void Player::setPosition(sf::Vector2f _position)
//{
//	player_sprite.setPosition(_position);
//}
//
//void Player::movePosition(sf::Vector2f _position)
//{
//	position += _position;
//}

void Player::Draw(sf::RenderWindow & _window)
{
	_window.draw(player_sprite);
}

sf::Sprite Player::getSprite()
{
	return player_sprite;
}

void Player::moveLeft()
{
	moveInt = 2;
}

void Player::moveRight()
{
	moveInt = 3;
}

void Player::moveUp()
{
	moveInt = 0;
}

void Player::moveDown()
{
	moveInt = 1;
}

void Player::masterMove()
{
	while (true)
	{
		if (moveInt == 0)
		{
			player_sprite.move(0.00f, -0.0001f);
		}
		if (moveInt == 1)
		{
			player_sprite.move(0.00f, 0.0001f);
		}
		if (moveInt == 2)
		{
			player_sprite.move(-0.0001f, 0.0f);
		}
		if (moveInt == 3)
		{
			player_sprite.move(0.0001f, 0.0f);
		}
	}
}


