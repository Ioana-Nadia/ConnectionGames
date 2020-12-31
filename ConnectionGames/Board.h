#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>

class Board
{
public:
	void createBoardMatrix();
	void drawBoard(int xCoord, int yCoord, int yProiection, int shapeSide, int  maxCol, int maxDepth, bool presentProiection);
	void repaint(sf::RenderWindow& window);
	bool verifyCoordinates(int& xCoord, int& yCoord, int& hexX, int& hexY);
	bool clickHexagon(int xCoord, int yCoord, sf::Color color);
	bool clickedPieRule(int posX, int posY, sf::RectangleShape& rectButton);
	void pieRule();
	void configurePieRule(sf::RectangleShape& rectButton, sf::Text& boardText, sf::Font& boardFont);
	void activatePieRuleButton(sf::RectangleShape& rectButton, sf::Text& boardText);
	void deactivatePieRuleButton(sf::RectangleShape& rectButton, sf::Text& boardText);
	void configureWindowDesign(sf::RectangleShape& rectangle);
	void playGame(int xCoord, int yCoord, int shapeSide, int maxCol, int maxDepth, int yProiection, bool presentProiection);
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape>> > getMatrix() const;
private:
	const int hexRadius = 20;
	const int xIncrease = 41, yIncrease = 38;
	const int nrLines = 23, nrColumns = 20;
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape>> > coordinatesMatrix;
};