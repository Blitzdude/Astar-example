#pragma once
#include <vector>
#include "ClosedList.h"
#include "SearchNode.h"


class SearchLevel
{
public:
	SearchLevel();
	~SearchLevel();

	bool init(const uint8_t* inputData, int width, int height);

	float getDeltaG(SearchNode* fromNode, SearchNode* toNode);
	float getH(SearchNode* fromPos, SearchNode* toPos);
	
	std::vector<Position> getAdjacentNodes(int posX, int posY);


	static double euclideanDist(double a, double b, double c, double d) { // pythagorian distance
		return sqrt(double((a - c) * (a - c) + (b - d) * (b - d)));
	}

	static double manhattanDist(double aX, double aY, double bX, double bY) { // block distance

		return abs(aX - bX) + abs(aY - bY);
	}
private:
	bool isWalkable(int x, int y);

	const uint8_t* m_levelData;
	int m_levelWidth;
	int m_levelHeight;
};

