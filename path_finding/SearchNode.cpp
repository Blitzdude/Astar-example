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
		printf("delta G: %f\n", deltaG);
		printf("prevnode G: %f\n", prevNode->G);
		float sum = deltaG + prevNode->G;
		printf("sum: %f\n", sum);
		assert(sum >= 0 && sum < 1000);
		G = sum;
		printf("prevNode adr: %p\n", prevNode);
	}

//	assert(G >= 0  && H >= 0)
}

// return the approximate of the total cost. 

SearchNode::~SearchNode()
{
}
