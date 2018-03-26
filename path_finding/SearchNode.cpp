#include "SearchNode.h"

SearchNode::SearchNode(Position currentPosition, float _H, float deltaG, SearchNode* prev) :
	prevNode(nullptr),
	pos(currentPosition),
	G(0), 
	H(_H)
{
	resetPrev(prev, deltaG);
}

// calculate total G for this node from previous node G value. 
// also calculates new F from new G and H
void 
SearchNode::resetPrev(SearchNode* prev, float deltaG)
{
	
	prevNode = prev;
	if (prevNode == nullptr)
		G = 0.0f;
	else
		G = deltaG + prevNode->G;

	F = G + H;
}

// return the approximate of the total cost. 
float
SearchNode::distance() const
{
	return F;
}

SearchNode::~SearchNode()
{
}
