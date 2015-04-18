#pragma once
#include "AvlNode.h"

class AvlIOFolder
{
public:
	AvlIOFolder(std::string directory) : directory(directory) {}

	void AllocateNode(AvlNode&);
	void WriteNode(AvlNode& node, int);
	void ReadNode(int, AvlNode&);

private:
	std::string directory;

	int latestFile = 0;
};

