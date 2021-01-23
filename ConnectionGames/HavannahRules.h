#pragma once
#include "Board.h"
#include "GameAttributes.h"
#include <iostream>

class HavannahRules: public GameAttributes {
public:
	void havannahEdges(std::vector<std::pair<int, int>>& edgesIndices);
	HavannahRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners);
	void havannahWhichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	bool isInCorner(std::pair<int, int>& indices, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners);
	void havannahEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners);
	bool firstWinningCondition(std::vector<bool>& foundEdges);
	bool secondWinningCondition(std::vector<bool>& foundCorners);
	bool havannahWinningCondition(std::vector<bool>& foundEdges, std::vector<bool>& foundCorners);
	bool havannahBfs(std::vector<bool>& foundEdges, int& matrixLine, int& matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, std::vector<std::pair<int, int>>& edgesIndices, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners);
private:
	const int havannahEdgesNumber = 6;
	const int havannahCornersNumber = 6;
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> > bfsMatrix;
};