#include "Node.h"

struct RbNode :
	public Node
{
	RbNode(std::string k, bool isBlack = false) : Node(k), isBlack(isBlack) {}

	RbNode *left = NULL;
	RbNode *right = NULL;
	RbNode *parent = NULL;

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

