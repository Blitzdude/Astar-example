#pragma once
#include <utility> // std::pair

typedef std::pair<int, int> Position;

class SearchNode
{
public:
	
	Position pos;		  // x and y position in the map
	float G;			  // Actual distance from the beginning point (A)
	float H;			  // Estimated heurestic distance to end point (B)
	SearchNode* prevNode; // Tells us the node, where we arrived to this node (previous/parent Node)
	const float getF() const { return G + H; };	// G + H

public:
	SearchNode(Position _position, float _H, float deltaG, SearchNode* prev = nullptr);
	~SearchNode();

	void resetPrev(SearchNode* prev, float deltaG);
	SearchNode* getPrev() { return this->prevNode; };
	
};

