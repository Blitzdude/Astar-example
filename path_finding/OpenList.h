#pragma once
#include "SearchNode.h"
#include <vector>
class OpenList
{
public:
	OpenList();
	~OpenList();

	void insertToOpenList(SearchNode* n);
	void sortOpenList();
	SearchNode* RemoveSmallestFFromOpenList();
	bool isEmpty();
	void clear();
private:
	std::vector<SearchNode> m_openList;
	// comparison function
	bool lessThan() {};
};

