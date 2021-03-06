#include <Game\Player.h>

Player::Player(std::string && fname)
{
	std::thread movement(&Player::updateMovement, this);
	movement.detach();
	collider.setSize(sf::Vector2f(0.01f, 0.01f));
	collider.setPosition(player_sprite.getPosition().x + 45.0f, player_sprite.getPosition().y + 60.0f);
	if (!player_texture.loadFromFile("..\\..\\Resources\\" + fname))
	{
		return;
	}
	player_sprite.setTexture(player_texture);
	player_sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	
}

Player::~Player()
{

}

void Player::KillThread()
{
	ThreadAlive = false;
}

void Player::Draw(sf::RenderWindow & _window)
{
	_window.draw(player_sprite);
}

sf::Sprite Player::getSprite()
{
	return player_sprite;
}

void Player::movePlayer(int _direction)
{
	switch (_direction)
	{
	case 0:
		movement_direction = 0;
		break;
	case 1:
		movement_direction = 1;
		break;
	case 2:
		movement_direction = 2;
		break;
	case 3:
		movement_direction = 3;
		break;
	}
}
//void Player::moveLeft()
//{
//	moveInt = 2;
//}
//
//void Player::moveRight()
//{
//	moveInt = 3;
//}
//
//void Player::moveUp()
//{
//	moveInt = 0;
//}
//
//void Player::moveDown()
//{
//	moveInt = 1;
//}

void Player::updateMovement()
{
	while (ThreadAlive == true)
	{
		if (movement_direction == 0)
		{
			player_sprite.move(0.00f, -0.0001f);
			//player_sprite.setPosition(player_sprite.getPosition().x, player_sprite.getPosition().y - 0.0001);yer_sprite.move(0.0f, -0.0001f);
		}
		if (movement_direction == 1)
		{
			//player_sprite.move(0.00f, 0.001f);
			player_sprite.move(0.0f, 0.0001f);
		}
		if (movement_direction == 2)
		{
			//player_sprite.move(-0.001f, 0.0f);
			player_sprite.move(-0.0001f, 0.0f);
		}
		if (movement_direction == 3)
		{
			//player_sprite.move(0.001f, 0.0f);
			player_sprite.move(0.0001f, 0.0f);
		}
	}
}


void Player::setPlayerID(int ID)
{
	playerID = ID;
}

int Player::getPlayerID()
{
	return playerID;
}

sf::RectangleShape* Player::getCollider()
{
	return &collider;
}


