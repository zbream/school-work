#include "Node.h"

struct RbNode :
	public Node
{
	RbNode(std::string k) : Node(k) {}

	RbNode *left = NULL;
	RbNode *right = NULL;

	bool isBlack = true;

	Node* GetLeft()
	{
		return left;
	}

	Node* GetRight()
	{
		return right;
	}
};

