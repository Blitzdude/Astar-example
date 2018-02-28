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
	bool isStart;		  //

public:
	SearchNode * prevNode; // Tells us the node, where we arrived to this node (previous/parent Node)
	SearchNode(const Position& currentPosition, float _H, float deltaG, bool truth, SearchNode* prev);
	~SearchNode();
	void resetPrev(SearchNode* prev, float deltaG);
	SearchNode* getPrev() { return this->prevNode; };
	float distance() const;
	//static bool lessThan(SearchNode* n1, SearchNode* n2);
	
};

