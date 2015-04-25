/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BIOFile.cpp
This class reads/writes B-tree nodes on the disk.
This version stores all nodes in a single, contiguous file. */

#include "BIOFile.h"

using namespace std;

BIOFile::BIOFile(string file) : stream(file, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary) {}

void BIOFile::AllocateNode(BNode& node)
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

void BIOFile::WriteNode(BNode& node)
{
	// move to record
	stream.seekp(getOffset(node.id));

	// write contents
	stream.put(node.isLeaf);
	writeInt(stream, node.n);

	// write (n) keys, counts
	for (int j = 0; j < node.n; ++j)
	{
		strncpy_s(buffer, node.keys[j].key.c_str(), KEY_WIDTH);
		stream.write(buffer, KEY_WIDTH + 1);
		writeInt(stream, node.keys[j].count);
	}

	// read (n+1) children; we don't need them if a leaf
	if (!node.isLeaf)
	{
		for (int j = 0; j < node.n + 1; ++j)
		{
			writeInt(stream, node.children[j]);
		}
	}
}

void BIOFile::ReadNode(int id, BNode& node)
{
	// move to record
	stream.seekg(getOffset(id));
	node.id = id;

	// read contents
	node.isLeaf = (stream.get() == 1);
	node.n = readInt(stream);

	// read (n) keys, counts
	for (int j = 0; j < node.n; ++j)
	{
		stream.read(buffer, KEY_WIDTH + 1);
		node.keys[j].key = string(buffer);
		node.keys[j].count = readInt(stream);
	}

	// read (n+1) children; we don't need them if a leaf
	if (!node.isLeaf)
	{
		for (int j = 0; j < node.n + 1; ++j)
		{
			node.children[j] = readInt(stream);
		}
	}
}

void BIOFile::writeInt(fstream& stream, int i)
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

int BIOFile::readInt(fstream& stream)
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