#include "HexRules.h"

void HexRules::hexEdges(std::vector<std::pair<int, int>>& edgesIndices)
{
	const int half = 10;
	const int secondHalf = 20;
	std::pair<int, int> newPair;
	newPair = std::pair<int, int>(0, 0);
	edgesIndices.push_back(newPair);
	for (int index = 1; index <= half; ++index) {
		newPair = std::pair<int, int>(index, 0);
		edgesIndices.push_back(newPair);
		newPair = std::pair<int, int>(index, index);
		edgesIndices.push_back(newPair);
	}
	for (int index = 1; index < half; ++index)
	{
		newPair = std::pair<int, int>(half + index, 0);
		edgesIndices.push_back(newPair);
		newPair = std::pair<int, int>(half + index, half - index);
		edgesIndices.push_back(newPair);
	}
	newPair = std::pair<int, int>(secondHalf, 0);
	edgesIndices.push_back(newPair);
}

HexRules::HexRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges)
{
	hexEdges(edgesIndices);
	foundEdges = std::vector<bool>(hexEdgesNumber, false);
}

bool HexRules::hexSpecialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	if (indices.first == 0 && indices.second == 0)
	{
		foundEdges[0] = true;
		foundEdges[1] = true;
		return true;
	}
	else {
		if (indices.first == 10 && indices.second == 0)
		{
			foundEdges[0] = true;
			foundEdges[3] = true;
			return true;
		}
		else
		{
			if (indices.first == 10 && indices.second == 10)
			{
				foundEdges[1] = true;
				foundEdges[2] = true;
				return true;
			}
			else
			{
				if (indices.first == 20 && indices.second == 0)
				{
					foundEdges[3] = true;
					foundEdges[2] = true;
					return true;
				}

			}
		}
	}
	return false;
}

void HexRules::hexWhichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	bool specialCase = hexSpecialCases(indices, foundEdges);
	if (specialCase == false)
	{
		if ((indices.first >= 1 && indices.first <= 9) && indices.second == 0)
			foundEdges[0] = true;
		else
		{
			if ((indices.first >= 11 && indices.first <= 19) && indices.second == 0)
				foundEdges[3] = true;
			else
			{
				if (indices.first == indices.second)
					foundEdges[1] = true;
				else
					foundEdges[2] = true;
			}
		}
	}
}

void HexRules::hexEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	std::cout << indices.first << " " << indices.second << "\n";
	if (isInEdge(edgesIndices, indices, 0, edgesIndices.size() - 1))
	{
		std::cout << "E in coaja!" << "\n";
		hexWhichEdge(indices, foundEdges);
	}
	for (int index = 0; index < foundEdges.size(); ++index)
		std::cout << foundEdges[index] << " ";
	std::cout << "\n";
}

bool HexRules::hexWinningCondition(std::vector<bool>& foundEdges)
{
	if ((foundEdges[0] == true && foundEdges[2] == true) || (foundEdges[1] == true && foundEdges[3] == true))
		return true;
	return false;
}

bool HexRules::hexBfs(std::vector<bool>& foundEdges, int& matrixLine, int& matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& matrix, std::vector<std::pair<int, int>>& edgesIndices)
{
	bfsMatrix = matrix;
	std::array<std::pair<int, int>, 6> directionsFirstHalf = { { std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(1, 0) } };
	std::array<std::pair<int, int>, 6> directionsMiddle = { { std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(1, -1) } };
	std::array<std::pair<int, int>, 6> directionsSecondHalf = { { std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(-1, 1), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(1, -1) } };
	std::queue<std::pair<int, int>> bfsQueue;
	std::pair<int, int> startPosition = std::pair<int, int>(matrixLine, matrixColumn);
	bfsQueue.push(startPosition);
	sf::Color color = std::get<2>(bfsMatrix[matrixLine][matrixColumn]).getFillColor();
	std::get<3>(bfsMatrix[matrixLine][matrixColumn]) = 1;
	int roadIndex = 2;
	while (!bfsQueue.empty())
	{
		std::pair<int, int> firstElement = bfsQueue.front();
		hexEdge(edgesIndices, firstElement, foundEdges);
		std::array<std::pair<int, int>, 6> neighboursDirections;
		if (firstElement.first >= 0 && firstElement.first <= 9)
			neighboursDirections = directionsFirstHalf;
		else
		{
			if (firstElement.first == 10)
				neighboursDirections = directionsMiddle;
			else
				neighboursDirections = directionsSecondHalf;
		}
		bfsCommonPart(bfsQueue, firstElement, bfsMatrix, neighboursDirections, roadIndex, color);
	}
	for (int i = 0; i < bfsMatrix.size(); ++i)
	{
		for (int j = 0; j < bfsMatrix[i].size(); ++j)
			std::cout << std::get<3>(bfsMatrix[i][j]) << " ";
		std::cout << "\n";
	}
	if (hexWinningCondition(foundEdges))
		return true;
	return false;
}
