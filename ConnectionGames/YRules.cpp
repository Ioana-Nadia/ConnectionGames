#include "YRules.h"

void YRules::yEdges(std::vector<std::pair<int, int>>& edgesIndices)
{
	const int limit = 12;
	std::pair<int, int> newPair = std::pair<int, int>(0, 0);
	edgesIndices.push_back(newPair);
	for (int index = 1; index < limit; ++index)
	{
		newPair = std::pair<int, int>(index, 0);
		edgesIndices.push_back(newPair);
		newPair = std::pair<int, int>(index, index);
		edgesIndices.push_back(newPair);
	}
	for (int index = 0; index <= limit; ++index)
	{
		newPair = std::pair<int, int>(limit, index);
		edgesIndices.push_back(newPair);
	}
	for (int i = 0; i < edgesIndices.size(); ++i)
		std::cout << edgesIndices[i].first << " " << edgesIndices[i].second << "\n";
}

YRules::YRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges)
{
	yEdges(edgesIndices);
	foundEdges = std::vector<bool>(yEdgesNumber, false);
}

bool YRules::ySpecialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	if (indices.first == 0 && indices.second == 0)
	{
		foundEdges[0] = true;
		foundEdges[1] = true;
		return true;
	}
	else
	{
		if (indices.first == 12 && indices.second == 12)
		{
			foundEdges[1] = true;
			foundEdges[2] = true;
			return true;
		}
		else
		{
			if (indices.first == 12 && indices.second == 0)
			{
				foundEdges[0] = true;
				foundEdges[2] = true;
				return true;
			}
		}
	}
	return false;
}

void YRules::yWhichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	bool specialCase = ySpecialCases(indices, foundEdges);
	if (!specialCase)
	{
		if ((indices.first >= 0 && indices.first <= 12) && indices.second == 0)
			foundEdges[0] = true;
		else
		{
			if (indices.first == indices.second)
				foundEdges[1] = true;
			else
				foundEdges[2] = true;
		}
	}
}

void YRules::yEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	std::cout << indices.first << " " << indices.second << "\n";
	if (isInEdge(edgesIndices, indices, 0, edgesIndices.size() - 1))
	{
		std::cout << "E in coaja!" << "\n";
		yWhichEdge(indices, foundEdges);
	}
	for (int index = 0; index < foundEdges.size(); ++index)
		std::cout << foundEdges[index] << " ";
	std::cout << "\n";
}

bool YRules::yWinningCondition(std::vector<bool>& foundEdges)
{
	if (foundEdges[0] == true && foundEdges[1] && foundEdges[2] == true)
		return true;
	return false;
}

bool YRules::yBfs(std::vector<bool>& foundEdges, int& matrixLine, int& matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& matrix, std::vector<std::pair<int, int>>& edgesIndices)
{
	bfsMatrix = matrix;
	std::array<std::pair<int, int>, 6> neighboursDirections = { { std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(1, 0) } };
	std::queue<std::pair<int, int>> bfsQueue;
	std::pair<int, int> startPosition = std::pair<int, int>(matrixLine, matrixColumn);
	bfsQueue.push(startPosition);
	sf::Color color = std::get<2>(bfsMatrix[matrixLine][matrixColumn]).getFillColor();
	std::get<3>(bfsMatrix[matrixLine][matrixColumn]) = 1;
	int roadIndex = 2;
	while (!bfsQueue.empty())
	{
		std::pair<int, int> firstElement = bfsQueue.front();
		yEdge(edgesIndices, firstElement, foundEdges);
		for (int index = 0; index < neighboursDirections.size(); ++index)
		{
			std::pair<int, int> coordinates = firstElement;
			coordinates.first = coordinates.first + neighboursDirections[index].first;
			coordinates.second = coordinates.second + neighboursDirections[index].second;
			if (checkHexagonNeighbour(coordinates, bfsMatrix, color) && std::get<3>(bfsMatrix[coordinates.first][coordinates.second]) == 0)
			{
				bfsQueue.push(coordinates);
				std::get<3>(bfsMatrix[coordinates.first][coordinates.second]) = roadIndex;
			}
		}
		++roadIndex;
		bfsQueue.pop();
	}
	for (int i = 0; i < bfsMatrix.size(); ++i)
	{
		for (int j = 0; j < bfsMatrix[i].size(); ++j)
			std::cout << std::get<3>(bfsMatrix[i][j]) << " ";
		std::cout << "\n";
	}
	if (yWinningCondition(foundEdges))
		return true;
	return false;
}
