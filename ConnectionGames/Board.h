#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Board
{
public:
	void createBoardMatrix();
	void drawBoard(int xCoord, int yCoord, int yProiection, int shapeSide, int  maxCol, int maxDepth, bool presentProiection);
	void repaint(sf::RenderWindow& window);
	bool verifyCoordinates(int& xCoord, int& yCoord, int& hexX, int& hexY);
	void clickHexagon(int xCoord, int yCoord);
	std::vector<std::vector<std::pair<int, int>> > getMatrix() const;
	std::vector<sf::CircleShape> getButtonsVector() const;
private:
	const int hexRadius = 20;
	const int xIncrease = 41, yIncrease = 38;
	const int nrLines = 23, nrColumns = 20;
	std::vector<std::vector<std::pair<int, int>> > coordinatesMatrix;
	std::vector<sf::CircleShape> hexButtons;
};