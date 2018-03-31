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
	
	const std::vector<SearchNode*>& getList() const { return m_openList; };

private:
	std::vector<SearchNode*> m_openList;
};

