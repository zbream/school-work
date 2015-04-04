#pragma once
#include "BstNode.h"

struct AvlNode :
	public BstNode
{
	AvlNode(std::string k) : BstNode(k) {}

	BstNode *parent = NULL;
	int BF = 0;
};

