#include "OpenList.h"
#include <algorithm>
#include <iostream>

OpenList::OpenList()
{
}


OpenList::~OpenList()
{
}

SearchNode * OpenList::findFromOpenList(Position pos)
{
	auto itr = m_openList.begin();
	for (; itr != m_openList.end(); itr++) {

		if ((itr->pos.first == pos.first) && (itr->pos.second == pos.second))
		{
			return &(*itr);
		}
	}
	return nullptr;
}

void OpenList::insertToOpenList(SearchNode * n)
{
	m_openList.push_back(*n);
}

void OpenList::sortOpenList()
{
	std::sort(m_openList.begin(), m_openList.end(), [](const SearchNode& n1, const SearchNode& n2) -> bool
	{
		return (n1.F > n2.F);
	});
	// DEBUG
	/*
	for (auto& it : m_openList)
	{
		std::cout << it.F << std::endl;
	}
	std::cout << "\n\n";
	*/
}

bool OpenList::isInOpenList(Position pos)
{
	if (findFromOpenList(pos) != nullptr)
		return true;
	else
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

