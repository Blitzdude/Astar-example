#pragma once
#include "SearchNode.h"
#include <vector>
class OpenList
{
public:
	OpenList();
	~OpenList();

	SearchNode* findFromOpenLIst(Position pos);
	void insertToOpenList(SearchNode* n);
	void sortOpenList();
	bool isInOpenList(Position pos);
	SearchNode* RemoveSmallestFFromOpenList();
	bool isEmpty();
	void clear();
private:
	std::vector<SearchNode> m_openList;
	// comparison function
	bool lessThan(float a, float b) { return a < b; };
	bool samePos(Position a, Position b) { return (a.first == b.first) && (a.second == b.second); };
};

