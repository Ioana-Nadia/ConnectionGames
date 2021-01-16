#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class GameAttributes
{
public:
	bool isInEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, int left, int right);
	bool checkHexagonNeighbour(std::pair<int, int>& position, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, sf::Color& color);
};