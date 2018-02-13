#pragma once
#include "SearchNode.h"

#include <map>

class ClosedList
{
public:

	ClosedList();
	~ClosedList();

	void addToClosedList(SearchNode* n);
	bool isInClosedList(Position pos);
	void clear();
private:
	std::map<Position, SearchNode*> m_closedList;
};

