#pragma once
#include <utility> // std::pair

typedef std::pair<int, int> Position;

class SearchNode
{
public:
	SearchNode* prevNode; // Tells us the node, where we arrived to this node (previous/parent Node)
	Position pos;		  // x and y position in the map
	float G;			  // Actual distance from the beginning point (A)
	float H;			  // Estimated heurestic distance to end point (B)
	float F;			  // G + H

public:
	SearchNode(const Position& currentPosition, float _H, float deltaG, SearchNode* prev);
	~SearchNode();
	void resetPrev(SearchNode* prev, float deltaG);
	float distance() const;
	//static bool lessThan(SearchNode* n1, SearchNode* n2);
	
};

