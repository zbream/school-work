#pragma once
#include "BNode.h"

class BIOFolder
{
public:
	BIOFolder(std::string directory) : directory(directory) {}

	void AllocateNode(BNode&);
	void WriteNode(BNode&, int);
	void ReadNode(int, BNode&);

private:
	std::string directory;

	int latestFile = 0;
};

