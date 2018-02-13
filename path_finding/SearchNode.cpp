#include "SearchNode.h"



SearchNode::SearchNode(const Position& currentPosition, float _H, float deltaG, SearchNode* prev) :
	prevNode(0),
	pos(currentPosition),
	G(0), 
	H(_H)
{
	resetPrev(prev, deltaG);
}


// calculate total G for this node from previous node G value. 
// also calculates new F from new G and H
void 
SearchNode::resetPrev(SearchNode * prev, float deltaG)
{
	
	prevNode = prev;
	if (prev == 0)
		G = 0.0f;
	else
		G = deltaG + prev->G;

	F = G + H;
}

// return the approximate of the total cost. 
float
SearchNode::distance() const
{
	return F;
}

// less than function for sorting
bool SearchNode::lessThan(SearchNode * n1, SearchNode * n2)
{
	
	return n1->distance() > n2->distance();
}


SearchNode::~SearchNode()
{
}
