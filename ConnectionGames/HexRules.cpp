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
	foundEdges = std::vector<bool>(edgesNumber, false);
}

const int HexRules::getEdgesNumber() const
{
	return this->edgesNumber;
}

bool HexRules::isInEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, int left, int right)
{
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (edgesIndices[middle] == indices)
			return true;
		if (indices.first == edgesIndices[middle].first)
		{
			if (indices.second > edgesIndices[middle].second)
				return isInEdge(edgesIndices, indices, middle + 1, right);
			return isInEdge(edgesIndices, indices, left, middle - 1);
		}
		else
		{
			if (indices.first > edgesIndices[middle].first)
				return isInEdge(edgesIndices, indices, middle + 1, right);
			return isInEdge(edgesIndices, indices, left, middle - 1);
		}
	}
	return false;
}

bool HexRules::specialCases(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
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

void HexRules::whichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	bool specialCase = specialCases(indices, foundEdges);
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

void HexRules::edge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	if (isInEdge(edgesIndices, indices, 0, edgesIndices.size() - 1))
		whichEdge(indices, foundEdges);
}

bool HexRules::winningCondition(std::vector<bool>& foundEdges)
{
	if ((foundEdges[0] == true && foundEdges[2] == true) || (foundEdges[1] == true && foundEdges[3] == true))
		return true;
	return false;
}

bool HexRules::checkHexagonNeighbour(std::pair<int, int>& position, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& matrix, sf::Color& color)
{
	const int nrLines = 23, nrColumns = 20;
	if ((position.first >= 0 && position.first < nrLines) && (position.second >= 0 && position.second < nrColumns))
		if (std::get<2>(matrix[position.first][position.second]).getFillColor() == color)
			return true;
	return false;
}

bool HexRules::hexBfs(std::vector<bool>& foundEdges, int matrixLine, int matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& matrix, std::array<std::pair<int, int>, 6>& neighboursDirections, std::vector<std::pair<int, int>>& edgesIndices)
{
	bfsMatrix = matrix;
	std::queue<std::pair<int, int>> bfsQueue;
	std::pair<int, int> startPosition = std::pair<int, int>(matrixLine, matrixColumn);
	bfsQueue.push(startPosition);
	sf::Color color = std::get<2>(bfsMatrix[matrixLine][matrixColumn]).getFillColor();
	std::get<3>(bfsMatrix[matrixLine][matrixColumn]) = 1;
	int roadIndex = 2;
	while (!bfsQueue.empty())
	{
		std::pair<int, int> firstElement = bfsQueue.front();
		edge(edgesIndices, firstElement, foundEdges);
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
	if (winningCondition(foundEdges))
		return true;
	return false;
}
