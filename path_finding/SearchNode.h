#pragma once
#include <utility> // std::pair

typedef std::pair<int, int> Position;

class SearchNode
{
public:
	
	Position pos;		  // x and y position in the map
	float G;			  // Actual distance from the beginning point (A)
	float H;			  // Estimated heurestic distance to end point (B)
	float F;			  // G + H

public:
	SearchNode(const Position& currentPosition, float _H, float deltaG, SearchNode* prev);
	~SearchNode();
	
	//bool operator() (const SearchNode &lhs, const SearchNode &rhs) { return lhs.F > rhs.F; };

	SearchNode * prevNode; // Tells us the node, where we arrived to this node (previous/parent Node)
	void resetPrev(SearchNode* prev, float deltaG);
	SearchNode* getPrev() { return this->prevNode; };
	float distance() const;
	//static bool lessThan(SearchNode* n1, SearchNode* n2);
	
};

