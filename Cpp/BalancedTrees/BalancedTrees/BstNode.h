#pragma once
#include <string>

struct BstNode
{
	BstNode(std::string k) : key(k), count(1) {}

	std::string key;
	int count;

	BstNode *left = NULL;
	BstNode *right = NULL;

	std::string Format()
	{
		return key + " " + std::to_string(count);
	}
};

