/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BIOFile.h
This class reads/writes B-tree nodes on the disk.
This version stores all nodes in a single, contiguous file. */

#include <fstream>
#include "BNode.h"

class BIOFile
{
public:
	BIOFile(std::string);

	/*
	Allocate a new node on the hard disk, populate the given node with its ID.
	*/
	void AllocateNode(BNode&);

	/*
	Write the given node on the hard disk, using its interna
	l ID.
	*/
	void WriteNode(BNode&);

	/*
	Read the specified node ID from the hard disk into the given node.
	*/
	void ReadNode(int, BNode&);

private:
	// max width, in bytes, of a single key
	static const int KEY_WIDTH = 27;

	// width, in bytes, of a node in the data file
	static const int NODE_WIDTH = 1 + sizeof(int) + ((KEY_WIDTH + 1 + sizeof(int)) * (2 * BNode::T - 1)) + (sizeof(int) * (2 * BNode::T));
	// leaf bit, n int, (2t-1) keys+terminator and count ints, (2t) children ints

	// io stream
	std::fstream stream;

	// the latest node number that has been allocated
	int latestNode = 0;

	// key i/o buffer
	char buffer[KEY_WIDTH + 1];

	/*
	Calculate the offset of the specified node number (1-based).
	*/
	static int getOffset(int id)
	{
		// node ids 1-based
		return (id - 1) * NODE_WIDTH;
	}

	/*
	Write an int, byte-by-byte, to the given fstream.
	Begins writing at the fstream's current write position.
	*/
	static void writeInt(std::fstream&, int);

	/*
	Read an int, byte-by-byte, from the given fstream.
	Begins reading at the fstream's current read position.
	*/
	static int readInt(std::fstream&);
};

