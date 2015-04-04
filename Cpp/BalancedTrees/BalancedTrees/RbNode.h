#pragma once
#include "BstNode.h"

struct RbNode :
	public BstNode
{
	RbNode(std::string k) : BstNode(k) {}

	bool isBlack = true;
};

