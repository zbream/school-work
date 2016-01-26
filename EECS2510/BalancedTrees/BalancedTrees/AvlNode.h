/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

AvlNode.h
This struct implements the Node as an AVL Tree node.
Distinguishing factor is the balance factor (BF), which initializes to 0. */

#include "Node.h"

struct AvlNode :
	public Node
{
	AvlNode(std::string key) : Node(key) {}

	AvlNode *left = NULL;
	AvlNode *right = NULL;

	// balance factor
	int BF = 0;

	Node* GetLeft()
	{
		return left;
	}

	Node* GetRight()
	{
		return right;
	}
};

