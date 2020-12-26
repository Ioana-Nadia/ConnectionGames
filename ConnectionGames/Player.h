#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
	Player(sf::Color color);
	sf::Color getPlayerColor();
private:
	sf::Color color;
};