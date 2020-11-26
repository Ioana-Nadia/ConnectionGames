#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(300, 300, 32), "Connection Games", sf::Style::Fullscreen);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		int x = 50, y = 50;
		while (x < 500) {
			sf::CircleShape hexagon(30, 6);
			hexagon.setPosition(x, y);
			hexagon.setFillColor(sf::Color::Cyan);
			hexagon.setOutlineThickness(3);
			hexagon.setOutlineColor(sf::Color::Red);
			window.draw(hexagon);
			x += 60;
		}
		window.display();
	}
	return 0;
}