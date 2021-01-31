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
	std::tuple<int, int, sf::CircleShape, int> defaultTuple = std::tuple<int, int, sf::CircleShape, int>(pairCoord, pairCoord, hexagon, -1);
	for (int index = 0; index < nrLines; ++index)
	{
		std::vector<std::tuple<int, int, sf::CircleShape, int>> line(nrColumns, defaultTuple);
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
			std::get<3>(coordinatesMatrix[index][secondIndex]) = 0;
			if (index != shapeSide - 1 && presentProiection)
			{
				std::get<0>(coordinatesMatrix[maxDepth - index][secondIndex]) = xCoord;
				std::get<1>(coordinatesMatrix[maxDepth - index][secondIndex]) = yProiection;
				std::get<2>(coordinatesMatrix[maxDepth - index][secondIndex]).setPosition(xCoord, yProiection);
				std::get<3>(coordinatesMatrix[maxDepth - index][secondIndex]) = 0;
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

bool Board::clickHexagon(int xCoord, int yCoord, sf::Color color, int& matrixLine, int& matrixColumn)
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
					matrixLine = index;
					matrixColumn = secondIndex;
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

void Board::configurePieRule(sf::RectangleShape& rectButton, sf::Text& boardText, sf::Font& boardFont)
{
	const int pieRuleX = 300;
	const int pieRuleY = 60;
	rectButton.setPosition(pieRuleX, pieRuleY);
	rectButton.setFillColor(sf::Color::Transparent);
	rectButton.setOutlineThickness(4);
	rectButton.setOutlineColor(sf::Color::Transparent);
	boardText.setFont(boardFont);
	boardText.setString("Pie rule?");
	boardText.setCharacterSize(25);
	const int textX = 340, textY = 75;
	boardText.setPosition(textX, textY);
	boardText.setOutlineThickness(2);
	boardText.setOutlineColor(sf::Color::Transparent);
	boardText.setFillColor(sf::Color::Transparent);
}

void Board::activatePieRuleButton(sf::RectangleShape& rectButton, sf::Text& boardText)
{
	sf::Color blueOutline(0, 0, 205);
	rectButton.setFillColor(sf::Color::Yellow);
	rectButton.setOutlineColor(blueOutline);
	boardText.setOutlineColor(blueOutline);
	boardText.setFillColor(sf::Color::White);
}

void Board::deactivatePieRuleButton(sf::RectangleShape& rectButton, sf::Text& boardText)
{
	rectButton.setFillColor(sf::Color::Transparent);
	rectButton.setOutlineColor(sf::Color::Transparent);
	boardText.setOutlineColor(sf::Color::Transparent);
	boardText.setFillColor(sf::Color::Transparent);
}

void Board::configureWindowDesign(sf::RectangleShape& rectangle)
{
	rectangle.setPosition(248, 0);
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(sf::Color::Black);
	sf::Color backColor(105, 105, 105);
	rectangle.setFillColor(backColor);
}

void Board::playGame(int xCoord, int yCoord, int shapeSide, int maxCol, int maxDepth, int yProiection, bool presentProiection, int chosenGameIndice)
{
	sf::RenderWindow window(sf::VideoMode(300, 300, 32), "Connection Games", sf::Style::Fullscreen);
	drawBoard(xCoord, yCoord, yProiection, shapeSide, maxCol, maxDepth, presentProiection);
	Player firstPlayer(sf::Color::White);
	Player secondPlayer(sf::Color::Black);
	std::queue<Player> turn;
	turn.push(firstPlayer);
	turn.push(secondPlayer);
	int moveNumber = 0;
	sf::Texture texture;
	texture.loadFromFile("boardBackground.jpg");
	sf::Sprite windowSprite;
	windowSprite.setTexture(texture);
	sf::RectangleShape rectangle(sf::Vector2f(1477, 1100));
	configureWindowDesign(rectangle);
	sf::RectangleShape rectButton(sf::Vector2f(180, 60));
	sf::Font boardFont;
	boardFont.loadFromFile("arial.TTF");
	sf::Text boardText;
	configurePieRule(rectButton, boardText, boardFont);
	sf::SoundBuffer Buffer;
	Buffer.loadFromFile("pieRuleRing.wav");
	sf::Sound sound;
	sound.setBuffer(Buffer);
	while (window.isOpen())
	{
		window.draw(windowSprite);
		window.draw(rectangle);
		if (moveNumber == 1)
		{
			activatePieRuleButton(rectButton, boardText);

		}
		window.draw(rectButton);
		window.draw(boardText);
		repaint(window);
		if (moveNumber == 1)
		{
			sound.play();
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int xCoord = sf::Mouse::getPosition().x;
					int yCoord = sf::Mouse::getPosition().y;
					Player currentTurn = turn.front();
					if (moveNumber == 1 && clickedPieRule(xCoord, yCoord, rectButton))
					{
						pieRule();
						turn.pop();
						turn.push(currentTurn);
						++moveNumber;
						deactivatePieRuleButton(rectButton, boardText);
						break;
					}
					int matrixLine = -1, matrixColumn = -1;
					if (clickHexagon(xCoord, yCoord, currentTurn.getPlayerColor(), matrixLine, matrixColumn) == true)
					{
						std::vector<std::pair<int, int>> edgesIndices;
						std::vector<bool> foundEdges;
						sf::Color playerColor = currentTurn.getPlayerColor();
						if (chosenGameIndice == 1)
						{
							const int havannahCornersNumber = 6;
							std::vector<bool> foundCorners;
							std::array<std::pair<int, int>, havannahCornersNumber> havannahCorners;
							HavannahRules obj(edgesIndices, foundEdges, havannahCorners, foundCorners);
							std::pair<int, int> newPair = std::pair<int, int>(matrixLine, matrixColumn);
							if ((obj.havannahBfs(foundEdges, matrixLine, matrixColumn, coordinatesMatrix, edgesIndices, havannahCorners, foundCorners) == true))
								std::cout << "HAVANNAH game won!";
							else
							{
								std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> > dfsMatrix;
								dfsMatrix = coordinatesMatrix;
								const int mark = 2;
								std::get<3>(dfsMatrix[matrixLine][matrixColumn]) = 1;
								if (obj.havannahCircleWinningCondition(matrixLine, matrixColumn, dfsMatrix, playerColor, mark) == true)
									std::cout << "HAVANNAH game won!";
							}
						}
						else
						{
							if (chosenGameIndice == 2)
							{
								HexRules hexObject(edgesIndices, foundEdges);
								if (hexObject.hexBfs(foundEdges, matrixLine, matrixColumn, coordinatesMatrix, edgesIndices) == true)
									std::cout << "HEX Game won!";
							}
							else
							{
								YRules yObject(edgesIndices, foundEdges);
								if (yObject.yBfs(foundEdges, matrixLine, matrixColumn, coordinatesMatrix, edgesIndices) == true)
									std::cout << "Y Game won!";
							}

						}

						turn.pop();
						turn.push(currentTurn);
						++moveNumber;
					}
					if (moveNumber == 2)
						deactivatePieRuleButton(rectButton, boardText);
				}
				break;
			}
		}
	}
}

std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int> > > Board::getMatrix() const
{
	return this->coordinatesMatrix;
}
