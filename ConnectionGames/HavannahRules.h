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
	void havannahCircle(int actualLine, int actualColumn, int beforeLine, int beforeColumn, int startLine, int startColumn, int steps, bool& isCircle, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, sf::Color color, const int mark);
	bool havannahCircleWinningCondition(int matrixLine, int matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> >& matrix, sf::Color color, const int mark);
private:
	const int havannahEdgesNumber = 6;
	const int havannahCornersNumber = 6;
	std::array<std::pair<int, int>, 6> directionsFirstHalf = { { std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(1, 0) } };
	std::array<std::pair<int, int>, 6> directionsMiddle = { { std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(1, -1) } };
	std::array<std::pair<int, int>, 6> directionsSecondHalf = { { std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(-1, 1), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(1, -1) } };
	std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>> > bfsMatrix;
};