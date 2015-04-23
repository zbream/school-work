#pragma once
#include <string>

struct AvlNode
{
	// record on drive
	int id;

	// payload
	std::string key;
	int count;

	int left;
	int right;

	int BF;
};