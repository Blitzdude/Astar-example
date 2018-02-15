#include "OpenList.h"
#include <algorithm>
#include <iostream>

OpenList::OpenList()
{
}


OpenList::~OpenList()
{
}

void OpenList::insertToOpenList(SearchNode * n)
{
	m_openList.push_back(*n);
}

void OpenList::sortOpenList()
{
	std::sort(m_openList.begin(), m_openList.end(), [](const SearchNode &a, const SearchNode &b)
	{
		return a.F > b.F;
	});
	// Debug 
	for (auto& itr : m_openList)
	{
		std::cout << itr.F << " ";
	}
	std::cout << "\n";
}

bool OpenList::isInOpenList(Position pos)
{

	return false;
}

SearchNode* OpenList::RemoveSmallestFFromOpenList()
{
	SearchNode* temp = &m_openList.back();
	m_openList.pop_back();
	return temp;
}

bool OpenList::isEmpty()
{
	return m_openList.empty();
}

void OpenList::clear()
{
	m_openList.clear();
}
