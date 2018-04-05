#include "SearchNode.h"
#include <assert.h>

SearchNode::SearchNode(Position _position, float _H, float deltaG, SearchNode* prev /*= nullptr*/) :
	prevNode(nullptr),
	pos(_position),
	G(0.0f), 
	H(_H)
{
	assert(G >= 0 && H >= 0);
	resetPrev(prev, deltaG);
}

// calculate total G for this node from previous node G value. 
// also calculates new F from new G and H
void 
SearchNode::resetPrev(SearchNode* prev, float deltaG)
{
	prevNode = prev;

	assert(this != prevNode);
	if (prevNode == nullptr)
		G = 0.0f;
	else {
		float sum = deltaG + prevNode->G;
		G = sum;
	}

//	assert(G >= 0  && H >= 0)
}

// return the approximate of the total cost. 

SearchNode::~SearchNode()
{
}
