/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

BstNode.h 
This struct implements the Node as a Binary Search Tree node. */

#include "Node.h"

struct BstNode : 
	public Node
{
	BstNode(std::string k) : Node(k) {}

	BstNode *left = NULL;
	BstNode *right = NULL;

	Node* GetLeft()
	{
		return left;
	}

	Node* GetRight()
	{
		return right;
	}
};

