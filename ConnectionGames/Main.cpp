#include "Board.h"
#include <queue>
#include "Player.h"

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
		while (window.isOpen())
		{
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
						if (moveNumber == 1)
						{
							newGame.pieRule();//if I pressed the button, call pieRule function
							turn.pop();
							turn.push(currentTurn);
						}
						else
							if (newGame.clickHexagon(xCoord, yCoord, currentTurn.getPlayerColor()) == true)
							{
								turn.pop();
								turn.push(currentTurn);
							}
						++moveNumber;
					}
					break;
				}
			}
		}
	}
	return 0;
}