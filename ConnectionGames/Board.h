#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Board
{
public:
	void createBoardMatrix();
	void drawBoard(sf::RenderWindow& window, int xCoord, int yCoord, int yProiection, int shapeSide, int  maxCol, int maxDepth, bool presentProiection);
	std::vector<std::vector<std::pair<int, int>> > getMatrix();
private:
	const int hexDiameter = 20;
	const int xIncrease = 41, yIncrease = 38;
	const int nrLines = 23, nrColumns = 20;
	std::vector<std::vector<std::pair<int, int>> > coordinatesMatrix;
};