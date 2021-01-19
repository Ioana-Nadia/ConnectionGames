#include "GameAttributes.h"

bool GameAttributes::isInEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, int left, int right)
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

bool GameAttributes::checkHexagonNeighbour(std::pair<int, int>& position, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& matrix, sf::Color& color)
{
	const int nrLines = 23, nrColumns = 20;
	if ((position.first >= 0 && position.first < nrLines) && (position.second >= 0 && position.second < nrColumns))
		if (std::get<2>(matrix[position.first][position.second]).getFillColor() == color)
			return true;
	return false;
}

void GameAttributes::bfsCommonPart(std::queue<std::pair<int, int>>& bfsQueue, std::pair<int, int>& firstElement, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& bfsMatrix, std::array<std::pair<int, int>, 6>& neighboursDirections, int& roadIndex, sf::Color& color)
{
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
