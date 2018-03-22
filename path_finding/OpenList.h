#pragma once
#include "SearchNode.h"
#include <vector>
class OpenList
{
public:
	OpenList();
	~OpenList();

	SearchNode* findFromOpenList(Position pos);
	void insertToOpenList(SearchNode* n);
	void sortOpenList();
	bool isInOpenList(Position pos);
	SearchNode* RemoveSmallestFFromOpenList();
	bool isEmpty();
	void clear();
	
	
private:
	//bool isFGreater(SearchNode &n1, SearchNode &n2) { return n1.F > n2.F; };
	std::vector<SearchNode> m_openList;
};

