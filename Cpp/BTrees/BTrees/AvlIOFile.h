#pragma once
#include <fstream>
#include "AvlNode.h"

class AvlIOFile
{
public:
	AvlIOFile(std::string);

	void AllocateNode(AvlNode&);
	void WriteNode(AvlNode&);
	void ReadNode(int, AvlNode&);

private:
	const static int KEY_LENGTH = 32;
	const static int NODE_WIDTH = KEY_LENGTH + 1 + 4 * 4;

	std::fstream fs;

	int latestNode = 0;

	char buffer[KEY_LENGTH + 1];

	static int getOffset(int i);
	static void writeInt(std::fstream&, unsigned int);
	static int readInt(std::fstream&);
};

