#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
	Player(sf::Color color)
	{
		this->color = color;
	}
	sf::Color getPlayerColor()
	{
		return this->color;
	}
private:
	sf::Color color;
};