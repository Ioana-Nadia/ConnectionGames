#pragma once
#include "Board.h"
#include "GameAttributes.h"
#include <iostream>

class HexRules: public GameAttributes {
public:
	void hexEdges(std::vector<std::pair<int, int>>& edgesIndices);
	HexRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges);
	bool hexSpecialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void hexWhichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void hexEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	bool hexWinningCondition(std::vector<bool>& foundEdges);
	bool hexBfs(std::vector<bool>& foundEdges, int& matrixLine, int& matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, std::vector<std::pair<int, int>>& edgesIndices);
private:
	const int hexEdgesNumber = 4;
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> > bfsMatrix;
};