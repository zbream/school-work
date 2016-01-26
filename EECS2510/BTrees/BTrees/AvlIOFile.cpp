/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

AvlIOFile.cpp
This class reads/writes AVL-tree nodes on the disk.
This version stores all nodes in a single, contiguous file. */

#include "AvlIOFile.h"

using namespace std;

AvlIOFile::AvlIOFile(string file) : stream(file, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary) {}

void AvlIOFile::AllocateNode(AvlNode& node)
{
	// get offset
	node.id = ++latestNode;

	// create space for node
	stream.seekp(getOffset(node.id));
	for (int j = 0; j < NODE_WIDTH; ++j)
	{
		stream.put('\0');
	}
}

void AvlIOFile::WriteNode(AvlNode& node)
{
	// move to record
	stream.seekp(getOffset(node.id));

	// write KEY_WIDTH characters + \0 terminator
	strncpy_s(buffer, node.key.c_str(), KEY_WIDTH);
	stream.write(buffer, KEY_WIDTH + 1);

	// write rest of data
	writeInt(stream, node.count);
	writeInt(stream, node.left);
	writeInt(stream, node.right);
	writeInt(stream, node.BF);
}

void AvlIOFile::ReadNode(int id, AvlNode& node)
{
	// move to record
	stream.seekg(getOffset(id));
	node.id = id;

	// read key
	stream.read(buffer, KEY_WIDTH + 1);
	node.key = string(buffer);

	// read rest of data
	node.count = readInt(stream);
	node.left = readInt(stream);
	node.right = readInt(stream);
	node.BF = readInt(stream);

}

void AvlIOFile::writeInt(fstream& stream, int i)
{
	// we want to write the int big-endian, for easier reading
	int k = 0;
	for (int j = 0; j < sizeof(int); ++j)
	{
		k <<= 8;
		k |= (i & 0xFF);
		i >>= 8;
	}

	// write int to stream
	for (int j = 0; j < sizeof(int); ++j)
	{
		stream.put(k & 0xFF);
		k >>= 8;
	}
}

int AvlIOFile::readInt(fstream& stream)
{
	int o = 0;

	// build int from stream
	for (int j = 0; j < sizeof(int); ++j)
	{
		o <<= 8;
		o |= (stream.get());
	}

	return o;
}