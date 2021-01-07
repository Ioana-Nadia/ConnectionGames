#pragma once
#include "Board.h"

class HexRules {
public:
	void hexEdges(std::vector<std::pair<int, int>>& edgesIndices);
	const int getEdgesNumber() const;
	bool isInEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, int left, int right);
	bool specialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void whichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	void edge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges);
	bool winningCondition(std::vector<int>& foundEdges);
private:
	const int edgesNumber = 4;
};