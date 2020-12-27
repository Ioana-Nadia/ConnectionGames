#include "Board.h"

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
		sf::RenderWindow startWindow(sf::VideoMode(300, 300, 32), "Connection Games", sf::Style::Fullscreen);
		sf::Texture startTexture;
		startTexture.loadFromFile("startWindow.jpeg");
		sf::Sprite startWindowSprite;
		startWindowSprite.setTexture(startTexture);
		while (startWindow.isOpen())
		{
			startWindow.draw(startWindowSprite);
			startWindow.display();
			sf::Event startEvent;
			while (startWindow.pollEvent(startEvent))
			{
				switch (startEvent.type)
				{
				case sf::Event::Closed:
					startWindow.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (startEvent.mouseButton.button == sf::Mouse::Left)
					{
						startWindow.close();
						Board newGame;
						newGame.playGame(xCoord, yCoord, shapeSide, maxCol, maxDepth, yProiection, presentProiection);
					}
					break;
				}
			}
		}
	}
	return 0;
}