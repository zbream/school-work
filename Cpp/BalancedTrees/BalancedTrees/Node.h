/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

Node.h
This struct acts as a generic binary tree node, carrying a key and count;
The L/R Nodes in this context are used to traverse the tree, not for modification. */

#pragma once
#include <string>

struct Node
{
	// a new node will only be created: 1) around a key, and 2) the key has been found once
	Node(std::string key) : key(key), count(1) {}

	std::string key;
	int count;

	virtual Node* GetLeft() = 0;
	virtual Node* GetRight() = 0;
};

