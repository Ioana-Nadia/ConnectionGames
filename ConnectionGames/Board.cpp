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

void Board::drawBoard(int xCoord, int yCoord, int yProiection, int shapeSide, int maxCol, int maxDepth, bool presentProiection)
{
	createBoardMatrix();
	int xAux = xCoord, yAux = yCoord;
	for (int index = 0; index < shapeSide; ++index)
	{
		for (int secondIndex = 0; secondIndex <= maxCol; ++secondIndex)
		{
			sf::CircleShape hexagon(hexRadius, 6);
			hexagon.setPosition(xCoord, yCoord);
			hexagon.setFillColor(sf::Color::Cyan);
			hexagon.setOutlineThickness(3);
			hexagon.setOutlineColor(sf::Color::Red);
			coordinatesMatrix[index][secondIndex] = std::pair<int, int>(xCoord, yCoord);
			hexButtons.push_back(hexagon);
			if (index != shapeSide - 1 && presentProiection)
			{
				sf::CircleShape hexagonSecond(hexRadius, 6);
				hexagonSecond.setPosition(xCoord, yProiection);
				hexagonSecond.setFillColor(sf::Color::Cyan);
				hexagonSecond.setOutlineThickness(3);
				hexagonSecond.setOutlineColor(sf::Color::Red);
				coordinatesMatrix[maxDepth - index][secondIndex] = std::pair<int, int>(xCoord, yProiection);
				hexButtons.push_back(hexagonSecond);
			}
			xCoord += xIncrease;
		}
		xAux -= hexRadius;
		yAux += yIncrease;
		xCoord = xAux;
		yCoord = yAux;
		if (presentProiection)
			yProiection -= yIncrease;
		++maxCol;
	}
}

void Board::repaint(sf::RenderWindow& window)
{
	int length = hexButtons.size();
	for (int index = 0; index < length; ++index) {
		window.draw(hexButtons[index]);
	}
	window.display();
}

bool Board::verifyCoordinates(int& xCoord, int& yCoord, int& hexX, int& hexY)
{
	if ((xCoord >= hexX && xCoord <= hexX + 2 * hexRadius) && (yCoord >= hexY && yCoord <= hexY + 2 * hexRadius))
		return true;
	return false;
}

void Board::clickHexagon(int xCoord, int yCoord)
{
	int length = hexButtons.size();
	for (int index = 0; index < length; ++index)
	{
		int hexX = hexButtons[index].getPosition().x;
		int hexY = hexButtons[index].getPosition().y;
		if (verifyCoordinates(xCoord, yCoord, hexX, hexY))
		{
			hexButtons[index].setFillColor(sf::Color::Magenta);
			break;
		}
	}
}

std::vector<std::vector<std::pair<int, int>>> Board::getMatrix() const
{
	return coordinatesMatrix;
}

std::vector<sf::CircleShape> Board::getButtonsVector() const
{
	return hexButtons;
}
