#include "Board.h"
#include <queue>
#include "Player.h"

void configurePieRule(sf::RectangleShape& rectButton, sf::Text& boardText, sf::Font& boardFont)
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

void activatePieRuleButton(sf::RectangleShape& rectButton, sf::Text& boardText)
{
	sf::Color blueOutline(0, 0, 205);
	rectButton.setFillColor(sf::Color::Yellow);
	rectButton.setOutlineColor(blueOutline);
	boardText.setOutlineColor(blueOutline);
	boardText.setFillColor(sf::Color::White);
}

void deactivatePieRuleButton(sf::RectangleShape& rectButton, sf::Text& boardText)
{
	rectButton.setFillColor(sf::Color::Transparent);
	rectButton.setOutlineColor(sf::Color::Transparent);
	boardText.setOutlineColor(sf::Color::Transparent);
	boardText.setFillColor(sf::Color::Transparent);
}

void configureWindowDesign(sf::RectangleShape& rectangle)
{
	rectangle.setPosition(248, 0);
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(sf::Color::Black);
	sf::Color backColor(105, 105, 105);
	rectangle.setFillColor(backColor);
}

int main()
{
	int choice;
	std::cin >> choice;
	int xCoord, yCoord, shapeSide, maxCol, maxDepth, yProiection;
	bool presentProiection = true, goodChoice = true;
	switch (choice) {
	case 1:
		xCoord = 735;
		yCoord = 180;
		shapeSide = 10;
		maxCol = 9;
		maxDepth = 18;
		yProiection = 864;
		presentProiection = true;
		break;
	case 2:
		xCoord = 928;
		yCoord = 135;
		shapeSide = 11;
		maxCol = 0;
		maxDepth = 21;
		yProiection = 895;
		presentProiection = true;
		break;
	case 3:
		xCoord = 910;
		yCoord = 250;
		shapeSide = 13;
		maxCol = 0;
		maxDepth = 12;
		yProiection = -100;
		presentProiection = false;
		break;
	default:
		std::cout << "What you just chose is not a valid option!!!";
		goodChoice = false;
	}
	if (goodChoice)
	{
		Board newGame;
		sf::RenderWindow window(sf::VideoMode(300, 300, 32), "Connection Games", sf::Style::Fullscreen);
		newGame.drawBoard(xCoord, yCoord, yProiection, shapeSide, maxCol, maxDepth, presentProiection);
		Player firstPlayer(sf::Color::White);
		Player secondPlayer(sf::Color::Black);
		std::queue<Player> turn;
		turn.push(firstPlayer);
		turn.push(secondPlayer);
		int moveNumber = 0;
		sf::Texture texture;
		if (!texture.loadFromFile("boardBackground.jpg"))
		{
			std::cout << "Photo not found!";
		}
		sf::Sprite windowSprite;
		windowSprite.setTexture(texture);
		sf::RectangleShape rectangle(sf::Vector2f(1477, 1100));
		configureWindowDesign(rectangle);
		sf::RectangleShape rectButton(sf::Vector2f(180, 60));
		sf::Font boardFont;
		if (!boardFont.loadFromFile("arial.TTF"))
			std::cout << "Font file not found!";
		sf::Text boardText;
		configurePieRule(rectButton, boardText, boardFont);
		while (window.isOpen())
		{
			window.draw(windowSprite);
			window.draw(rectangle);
			if (moveNumber == 1)
				activatePieRuleButton(rectButton, boardText);
			window.draw(rectButton);
			window.draw(boardText);
			newGame.repaint(window);
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
						if (moveNumber == 1 && newGame.clickedPieRule(xCoord, yCoord, rectButton))
						{
							newGame.pieRule();
							turn.pop();
							turn.push(currentTurn);
							++moveNumber;
							deactivatePieRuleButton(rectButton, boardText);
							break;
						}
						if (newGame.clickHexagon(xCoord, yCoord, currentTurn.getPlayerColor()) == true)
						{
							turn.pop();
							turn.push(currentTurn);
						}
						++moveNumber;
						if(moveNumber == 2)
							deactivatePieRuleButton(rectButton, boardText);
					}
					break;
				}
			}
		}
	}
	return 0;
}