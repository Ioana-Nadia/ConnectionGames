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
	if (!specialCases(indices, foundEdges))
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

bool HexRules::winningCondition(std::vector<int>& foundEdges)
{
	if ((foundEdges[0] == true && foundEdges[2] == true) || (foundEdges[1] == true && foundEdges[3] == true))
		return true;
	return false;
}
