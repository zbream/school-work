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

