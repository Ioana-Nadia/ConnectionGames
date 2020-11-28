#include "Board.h"

void Board::createBoardMatrix()
{
	const int pairCoord = -100;
	std::pair<int, int> defaultPair = std::pair<int, int>(pairCoord, pairCoord);
	for (int index = 0; index < nrLines; ++index)
	{
		std::vector<std::pair<int, int>> line(nrColumns, defaultPair);
		coordinatesMatrix.push_back(line);
	}
}

void Board::drawBoard(sf::RenderWindow& window, int xCoord, int yCoord, int yProiection, int shapeSide, int maxCol, int maxDepth, bool presentProiection)
{
	createBoardMatrix();
	int xAux = xCoord, yAux = yCoord;
	for (int index = 0; index < shapeSide; ++index)
	{
		for (int secondIndex = 0; secondIndex <= maxCol; ++secondIndex)
		{
			sf::CircleShape hexagon(hexDiameter, 6);
			hexagon.setPosition(xCoord, yCoord);
			hexagon.setFillColor(sf::Color::Cyan);
			hexagon.setOutlineThickness(3);
			hexagon.setOutlineColor(sf::Color::Red);
			window.draw(hexagon);
			coordinatesMatrix[index][secondIndex] = std::pair<int, int>(xCoord, yCoord);
			if (index != shapeSide - 1 && presentProiection)
			{
				sf::CircleShape hexagonSecond(hexDiameter, 6);
				hexagonSecond.setPosition(xCoord, yProiection);
				hexagonSecond.setFillColor(sf::Color::Cyan);
				hexagonSecond.setOutlineThickness(3);
				hexagonSecond.setOutlineColor(sf::Color::Red);
				window.draw(hexagonSecond);
				coordinatesMatrix[maxDepth - index][secondIndex] = std::pair<int, int>(xCoord, yProiection);
			}
			xCoord += xIncrease;
		}
		xAux -= hexDiameter;
		yAux += yIncrease;
		xCoord = xAux;
		yCoord = yAux;
		if (presentProiection)
			yProiection -= yIncrease;
		++maxCol;
	}
}

std::vector<std::vector<std::pair<int, int>>> Board::getMatrix()
{
	return coordinatesMatrix;
}
