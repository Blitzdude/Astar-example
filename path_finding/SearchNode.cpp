#include "SearchNode.h"
#include <assert.h>

SearchNode::SearchNode(Position currentPosition, float _H, float deltaG, SearchNode* prev) :
	prevNode(nullptr),
	pos(currentPosition),
	G(0.0f), 
	H(_H),
	F(0.0f)
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
		printf("%f\n", deltaG);
		printf("%f\n", prevNode->G);
		float sum = deltaG + prevNode->G;
		printf("%f\n", sum);
		G = sum;
		printf("%f\n\n", G);
		assert(fabsf((deltaG + prevNode->G) - G) < 0.0001f);
	}

	assert(G >= 0  && H >= 0);
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
