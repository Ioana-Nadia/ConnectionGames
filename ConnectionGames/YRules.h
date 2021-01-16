#pragma once
#include "Board.h"
#include "GameAttributes.h"

class YRules: public GameAttributes {
public:
	void yEdges(std::vector<std::pair<int, int>>& edgesIndices);
	YRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges);
	bool ySpecialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void yWhichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void yEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	bool yWinningCondition(std::vector<bool>& foundEdges);
	bool yBfs(std::vector<bool>& foundEdges, int& matrixLine, int& matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, std::vector<std::pair<int, int>>& edgesIndices);
private:
	const int yEdgesNumber = 3;
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> > bfsMatrix;
};