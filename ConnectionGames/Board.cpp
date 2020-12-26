#include "Board.h"

void Board::createBoardMatrix()
{
	const int pairCoord = -100;
	sf::CircleShape hexagon(hexRadius, 6);
	hexagon.setPosition(pairCoord, pairCoord);
	hexagon.setFillColor(sf::Color::Cyan);
	hexagon.setOutlineThickness(3);
	hexagon.setOutlineColor(sf::Color::Red);
	std::tuple<int, int, sf::CircleShape> defaultTuple = std::tuple<int, int, sf::CircleShape>(pairCoord, pairCoord, hexagon);
	for (int index = 0; index < nrLines; ++index)
	{
		std::vector<std::tuple<int, int, sf::CircleShape>> line(nrColumns, defaultTuple);
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
			std::get<0>(coordinatesMatrix[index][secondIndex]) = xCoord;
			std::get<1>(coordinatesMatrix[index][secondIndex]) = yCoord;
			std::get<2>(coordinatesMatrix[index][secondIndex]).setPosition(xCoord, yCoord);
			if (index != shapeSide - 1 && presentProiection)
			{
				std::get<0>(coordinatesMatrix[maxDepth - index][secondIndex]) = xCoord;
				std::get<1>(coordinatesMatrix[maxDepth - index][secondIndex]) = yProiection;
				std::get<2>(coordinatesMatrix[maxDepth - index][secondIndex]).setPosition(xCoord, yProiection);
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
	int lengthMatrix = coordinatesMatrix.size();
	for (int index = 0; index < lengthMatrix; ++index)
	{
		int lengthLine = coordinatesMatrix[index].size();
		for (int secondIndex = 0; secondIndex < lengthLine; ++secondIndex)
			if (std::get<0>(coordinatesMatrix[index][secondIndex]) != -100 && std::get<1>(coordinatesMatrix[index][secondIndex]) != -100)
				window.draw(std::get<2>(coordinatesMatrix[index][secondIndex]));
	}
	window.display();
}

bool Board::verifyCoordinates(int& xCoord, int& yCoord, int& hexX, int& hexY)
{
	if ((xCoord >= hexX && xCoord <= hexX + 2 * hexRadius) && (yCoord >= hexY && yCoord <= hexY + 2 * hexRadius))
		return true;
	return false;
}

bool Board::clickHexagon(int xCoord, int yCoord, sf::Color color)
{
	int lengthMatrix = coordinatesMatrix.size();
	for (int index = 0; index < lengthMatrix; ++index)
	{
		int lengthLine = coordinatesMatrix[index].size();
		for (int secondIndex = 0; secondIndex < lengthLine; ++secondIndex)
		{
			int hexX = std::get<2>(coordinatesMatrix[index][secondIndex]).getPosition().x;
			int hexY = std::get<2>(coordinatesMatrix[index][secondIndex]).getPosition().y;
			if (verifyCoordinates(xCoord, yCoord, hexX, hexY))
			{
				if (std::get<2>(coordinatesMatrix[index][secondIndex]).getFillColor() == sf::Color::Cyan)
				{
					std::get<2>(coordinatesMatrix[index][secondIndex]).setFillColor(color);
					return true;
				}
				break;
			}
		}
	}
	return false;
}

void Board::pieRule()
{
	int lengthMatrix = coordinatesMatrix.size();
	for (int index = 0; index < lengthMatrix; ++index)
	{
		int lengthLine = coordinatesMatrix[index].size();
		for (int secondIndex = 0; secondIndex < lengthLine; ++secondIndex)
			if (std::get<2>(coordinatesMatrix[index][secondIndex]).getFillColor() == sf::Color::White)
				std::get<2>(coordinatesMatrix[index][secondIndex]).setFillColor(sf::Color::Black);
	}
}

std::vector<std::vector<std::tuple<int, int, sf::CircleShape> > > Board::getMatrix() const
{
	return this->coordinatesMatrix;
}
