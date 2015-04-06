#include "Node.h"

struct AvlNode :
	public Node
{
	AvlNode(std::string k) : Node(k) {}

	AvlNode *left = NULL;
	AvlNode *right = NULL;

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

