#pragma once
#include <vector>
#include <queue>
#include <array>
#include <SFML/Graphics.hpp>

class GameAttributes
{
public:
	bool isInEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, int left, int right);
	bool checkHexagonNeighbour(std::pair<int, int>& position, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, sf::Color& color);
	void bfsCommonPart(std::queue<std::pair<int, int>>& bfsQueue, std::pair<int, int>& firstElement, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& bfsMatrix, std::array<std::pair<int, int>, 6>& neighboursDirections, int& roadIndex, sf::Color& color);
};