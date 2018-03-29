#include "OpenList.h"
#include <algorithm>
#include <iostream>

namespace {
bool compareGreater(const SearchNode &a, const SearchNode &b)
{
	return a.F > b.F;
}

}

OpenList::OpenList()
{
}


OpenList::~OpenList()
{
}


const SearchNode * OpenList::findFromOpenList(Position pos)
{
	for (auto itr = m_openList.begin(); itr != m_openList.end(); itr++) {

		if (itr->pos.first == pos.first && itr->pos.second == pos.second)
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
	std::sort(m_openList.begin(), m_openList.end(), compareGreater);/*, [](const SearchNode &lhs, const SearchNode &rhs)
	{ return lhs.F > rhs.F; });*/
	
	// DEBUG
	/*
	for (auto& it : m_openList)
	{
		std::cout << " " << it.F << " " << std::endl;
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

