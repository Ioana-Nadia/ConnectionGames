#include "Board.h"

void setOutlineButton(sf::CircleShape& button, const int thickness)
{
	button.setOutlineThickness(thickness);
	button.setOutlineColor(sf::Color::Black);
}

void setLogo(sf::CircleShape& button, sf::Texture& texture, std::string& path, int rectInt)
{
	texture.loadFromFile(path);
	button.setTexture(&texture);
	button.setTextureRect(sf::IntRect(rectInt, 0, 100, 100));
}

void setLogoPhotos(sf::CircleShape& havLogo, sf::CircleShape& hexLogo, sf::CircleShape& yLogo, sf::Texture& havTexture, sf::Texture& hexTexture, sf::Texture& yTexture)
{
	std::string havPath = "HavannahBoard.png", hexPath = "HexBoard.png", yPath = "YBoard.png";
	setLogo(havLogo, havTexture, havPath, 0);
	havLogo.setPosition(500, 250);
	setLogo(hexLogo, hexTexture, hexPath, 0);
	hexLogo.setPosition(150, 250);
	setLogo(yLogo, yTexture, yPath, -2);
	yLogo.setPosition(850, 250);
	const int thickness = 2;
	setOutlineButton(havLogo, thickness);
	setOutlineButton(hexLogo, thickness);
	setOutlineButton(yLogo, thickness);
}

bool chosenGame(sf::CircleShape& button,int x, int y, int diameter)
{
	int xCoord = button.getPosition().x;
	int yCoord = button.getPosition().y;
	if ((x >= xCoord && x <= xCoord + diameter) && (y >= yCoord && y <= yCoord + diameter))
		return true;
	return false;
}

void chosenGameAttributes(sf::CircleShape& havLogo, sf::CircleShape& hexLogo, sf::CircleShape& yLogo, int& x, int& y, int& xCoord, int& yCoord, int& shapeSide, int& maxCol, int& maxDepth, int& yProiection, bool& presentProiection)
{
	int diameter = 200;
	if (chosenGame(havLogo, x, y, diameter))
	{
		xCoord = 735;
		yCoord = 180;
		shapeSide = 10;
		maxCol = 9;
		maxDepth = 18;
		yProiection = 864;
		presentProiection = true;
	}
	else
	{
		if (chosenGame(hexLogo, x, y, diameter))
		{
			xCoord = 928;
			yCoord = 135;
			shapeSide = 11;
			maxCol = 0;
			maxDepth = 21;
			yProiection = 895;
			presentProiection = true;
		}
		else
		{
			if (chosenGame(yLogo, x, y, diameter))
			{
				xCoord = 910;
				yCoord = 250;
				shapeSide = 13;
				maxCol = 0;
				maxDepth = 12;
				yProiection = -100;
				presentProiection = false;
			}
		}
	}
}

bool verifyAttributes(int& xCoord, int& yCoord, int& shapeSide, int& maxCol, int& maxDepth, int& yProiection, bool& presentProiection)
{
	if (xCoord != -100 && yCoord != -100 && shapeSide != -100 && maxCol != -100 && maxDepth != -100)
		return true;
	return false;
}

int main()
{
	int xCoord = -100, yCoord = -100, shapeSide = -100, maxCol = -100, maxDepth= -100, yProiection = -100;
	bool presentProiection = true;
	sf::RenderWindow startWindow(sf::VideoMode(300, 300, 32), "Connection Games", sf::Style::Fullscreen);
	sf::Texture startTexture, havTexture, hexTexture, yTexture;
	sf::CircleShape havLogo(100), hexLogo(100), yLogo(100);
	setLogoPhotos(havLogo, hexLogo, yLogo, havTexture, hexTexture, yTexture);
	startTexture.loadFromFile("startWindow.jpeg");
	sf::Sprite startWindowSprite;
	startWindowSprite.setTexture(startTexture);
	while (startWindow.isOpen())
	{
		startWindow.draw(startWindowSprite);
		startWindow.draw(havLogo);
		startWindow.draw(hexLogo);
		startWindow.draw(yLogo);
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
					int x = sf::Mouse::getPosition().x;
					int y = sf::Mouse::getPosition().y;
					chosenGameAttributes(havLogo, hexLogo, yLogo, x, y, xCoord, yCoord, shapeSide, maxCol, maxDepth, yProiection, presentProiection);	
					if (verifyAttributes(xCoord, yCoord, shapeSide, maxCol, maxDepth, yProiection, presentProiection))
					{
						startWindow.close();
						Board newGame;
						newGame.playGame(xCoord, yCoord, shapeSide, maxCol, maxDepth, yProiection, presentProiection);
					}
				}
				break;
			}
		}
	}
	return 0;
}