#include "Player.h"

Player::Player(sf::Color color)
{
	this->color = color;
}

sf::Color Player::getPlayerColor()
{
	return this->color;
}
