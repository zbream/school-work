#include "AvlIOFile.h"

using namespace std;

AvlIOFile::AvlIOFile(string file) : fs(file, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary) {}

void AvlIOFile::AllocateNode(AvlNode& node)
{
	// get offset
	node.id = ++latestNode;
	node.key = "";
	node.count = 0;
	node.left = 0;
	node.right = 0;
	node.BF = 0;

	fs.seekp(getOffset(node.id));
	for (int j = 0; j < NODE_WIDTH; j++)
	{
		fs.put('\0');
	}
}

void AvlIOFile::WriteNode(AvlNode& node)
{
	// move to record
	fs.seekp(getOffset(node.id));

	// write KEY_WIDTH characters + \0 terminator
	strncpy_s(buffer, node.key.c_str(), KEY_LENGTH);
	fs.write(buffer, KEY_LENGTH + 1);

	// write rest of data
	writeInt(fs, node.count);
	writeInt(fs, node.left);
	writeInt(fs, node.right);
	writeInt(fs, node.BF);
}

void AvlIOFile::ReadNode(int i, AvlNode& node)
{
	// move to record
	fs.seekg(getOffset(i));
	node.id = i;

	// read key
	fs.read(buffer, KEY_LENGTH + 1);
	node.key = string(buffer);

	// read rest of data
	node.count = readInt(fs);
	node.left = readInt(fs);
	node.right = readInt(fs);
	node.BF = readInt(fs);

}

int AvlIOFile::getOffset(int i)
{
	return (i-1) * 49;
}

void AvlIOFile::writeInt(fstream& fs, unsigned int i)
{
	fs.put((i & 0xFF000000) >> 24);
	fs.put((i & 0xFF0000) >> 16);
	fs.put((i & 0xFF00) >> 8);
	fs.put((i & 0xFF));
}

int AvlIOFile::readInt(fstream& fs)
{
	int out = 0;
	char c;
	for (int j = 0; j < 4; j++)
	{
		fs.get(c);
		out <<= 8;
		out |= (c & 0xFF);
	}

	return out;
}