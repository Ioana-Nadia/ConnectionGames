#include "Board.h"

void Board::createBoardMatrix()
{
	const int pairCoord = -100;
	sf::CircleShape hexagon(hexRadius, 6);
	hexagon.setPosition(pairCoord, pairCoord);
	sf::Color hexColor(176, 224, 230);
	hexagon.setFillColor(hexColor);
	hexagon.setOutlineThickness(3);
	sf::Color outline(0, 0, 205);
	hexagon.setOutlineColor(outline);
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
	sf::Color hexColor(176, 224, 230);
	for (int index = 0; index < lengthMatrix; ++index)
	{
		int lengthLine = coordinatesMatrix[index].size();
		for (int secondIndex = 0; secondIndex < lengthLine; ++secondIndex)
		{
			int hexX = std::get<2>(coordinatesMatrix[index][secondIndex]).getPosition().x;
			int hexY = std::get<2>(coordinatesMatrix[index][secondIndex]).getPosition().y;
			if (verifyCoordinates(xCoord, yCoord, hexX, hexY))
			{
				if (std::get<2>(coordinatesMatrix[index][secondIndex]).getFillColor() == hexColor)
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

bool Board::clickedPieRule(int posX, int posY, sf::RectangleShape& rectButton)
{
	const int rectPosX = rectButton.getPosition().x;
	const int rectPosY = rectButton.getPosition().y;
	if ((posX >= rectPosX && posX <= rectPosX + 180) && (posY >= rectPosY && posY <= rectPosY + 60))
		return true;
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
