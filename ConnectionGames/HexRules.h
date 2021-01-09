#pragma once
#include "Board.h"
#include <iostream>
#include <queue>
#include <array>

class HexRules {
public:
	void hexEdges(std::vector<std::pair<int, int>>& edgesIndices);
	HexRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges);
	const int getEdgesNumber() const;
	bool isInEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, int left, int right);
	bool specialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void whichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void edge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	bool winningCondition(std::vector<bool>& foundEdges);
	bool checkHexagonNeighbour(std::pair<int, int>& position, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, sf::Color& color);
	bool hexBfs(std::vector<bool>& foundEdges, int matrixLine, int matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, std::array<std::pair<int, int>, 6>& neighboursDirections, std::vector<std::pair<int, int>>& edgesIndices);
private:
	const int edgesNumber = 4;
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> > bfsMatrix;
};