/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

RbNode.h
This struct implements the Node as a Red-Black Tree node.
Distinguishing factor is the color bit (isBlack), which is initialized in the ctor.
Also, the parent pointer, which initializes to NULL. */

#include "Node.h"

struct RbNode :
	public Node
{
	// Initialize a new RbNode, of the given color (default: Red)
	RbNode(std::string k, bool isBlack = false) : Node(k), isBlack(isBlack) {}

	RbNode *left = NULL;
	RbNode *right = NULL;
	RbNode *parent = NULL;

	// color of the node (red == !isBlack)
	bool isBlack;

	Node* GetLeft()
	{
		return left;
	}

	Node* GetRight()
	{
		return right;
	}
};

