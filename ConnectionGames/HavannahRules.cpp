#include "HavannahRules.h"

void HavannahRules::havannahEdges(std::vector<std::pair<int, int>>& edgesIndices)
{
	std::pair<int, int> newPair;
	for (int index = 1; index < 9; ++index)
	{
		newPair = std::pair<int, int>(0, index);
		edgesIndices.push_back(newPair);
	}
	int columnValue = 17;
	for (int index = 1; index <= 17; ++index)
	{
		if (index > 9)
		{
			newPair = std::pair<int, int>(index, 0);
			edgesIndices.push_back(newPair);
			newPair = std::pair<int, int>(index, columnValue);
			edgesIndices.push_back(newPair);
			--columnValue;
		}
		else
		{
			if (index != 9)
			{
				newPair = std::pair<int, int>(index, 0);
				edgesIndices.push_back(newPair);
				newPair = std::pair<int, int>(index, index + 10);
				edgesIndices.push_back(newPair);
			}
		}
	}
	for (int index = 1; index < 9; ++index)
	{
		newPair = std::pair<int, int>(18, index);
		edgesIndices.push_back(newPair);
	}
	for (int i = 0; i < edgesIndices.size(); ++i)
		std::cout << edgesIndices[i].first << " " << edgesIndices[i].second << "\n";
}

HavannahRules::HavannahRules(std::vector<std::pair<int, int>>& edgesIndices, std::vector<bool>& foundEdges, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners)
{
	havannahEdges(edgesIndices);
	foundEdges = std::vector<bool>(havannahEdgesNumber, false);
	foundCorners = std::vector<bool>(havannahCornersNumber, false);
	havannahCorners = { { std::make_pair(0, 0), std::make_pair(0, 9), std::make_pair(9, 18), std::make_pair(18, 9), std::make_pair(18, 0), std::make_pair(9, 0) } };
}

void HavannahRules::havannahWhichEdge(std::pair<int, int>& indices, std::vector<bool>& foundEdges)
{
	if ((indices.second > 0 && indices.second <= 8) && indices.first == 0)
		foundEdges[0] = true;
	else
	{
		if (indices.second == 0 && (indices.first >= 0 && indices.first <= 8))
			foundEdges[5] = true;
		else
		{
			if (indices.second == 0 && (indices.first >= 10 && indices.first <= 17))
				foundEdges[4] = true;
			else
			{
				if ((indices.first >= 0 && indices.first <= 9) && (indices.second >= 10 && indices.second <= 18))
					foundEdges[1] = true;
				else
				{
					if (indices.first == 18 && (indices.second >= 1 && indices.second <= 8))
						foundEdges[3] = true;
					else
						foundEdges[2] = true;
				}
			}
		}
	}
}

bool HavannahRules::isInCorner(std::pair<int, int>& indices, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners)
{
	for (int index = 0; index < havannahCornersNumber; ++index)
		if (indices == havannahCorners[index])
		{
			foundCorners[index] = true;
			return true;
		}
	return false;
}

void HavannahRules::havannahEdge(std::vector<std::pair<int, int>>& edgesIndices, std::pair<int, int>& indices, std::vector<bool>& foundEdges, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners)
{
	std::cout << indices.first << " " << indices.second << "\n";
	if (isInEdge(edgesIndices, indices, 0, edgesIndices.size() - 1))
	{
		std::cout << "E in coaja!" << "\n";
		havannahWhichEdge(indices, foundEdges);
	}
	std::cout << "Margini: ";
	for (int index = 0; index < foundEdges.size(); ++index)
		std::cout << foundEdges[index] << " ";
	std::cout << "\n";
	if (isInCorner(indices, havannahCorners, foundCorners))
	{
		std::cout << "E colt!" << "\n";	
	}
	std::cout << "Colturi: ";
	for (int index = 0; index < foundCorners.size(); ++index)
			std::cout << foundCorners[index] << " ";
	std::cout << "\n";
}

bool HavannahRules::firstWinningCondition(std::vector<bool>& foundEdges)
{
	int number = 0;
	for (int index = 0; index < havannahEdgesNumber; ++index)
		if (foundEdges[index] == 1)
			++number;
	if (number >= 3)
		return true;
	return false;
}

bool HavannahRules::secondWinningCondition(std::vector<bool>& foundCorners)
{
	int number = 0;
	for (int index = 0; index < havannahCornersNumber; ++index)
		if (foundCorners[index] == 1)
			++number;
	if (number >= 2)
		return true;
	return false;
}

bool HavannahRules::havannahWinningCondition(std::vector<bool>& foundEdges, std::vector<bool>& foundCorners)
{
	if (firstWinningCondition(foundEdges) || secondWinningCondition(foundCorners))
		return true;
	return false;
}

bool HavannahRules::havannahBfs(std::vector<bool>& foundEdges, int& matrixLine, int& matrixColumn, std::vector<std::vector<std::tuple<int, int, sf::CircleShape, int>>>& matrix, std::vector<std::pair<int, int>>& edgesIndices, std::array<std::pair<int, int>, 6>& havannahCorners, std::vector<bool>& foundCorners)
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
		havannahEdge(edgesIndices, firstElement, foundEdges, havannahCorners, foundCorners);
		std::array<std::pair<int, int>, 6> neighboursDirections;
		if (firstElement.first >= 0 && firstElement.first < 9)
			neighboursDirections = directionsFirstHalf;
		else
		{
			if (firstElement.first == 9)
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
	if (havannahWinningCondition(foundEdges, foundCorners))
		return true;
	return false;
}
