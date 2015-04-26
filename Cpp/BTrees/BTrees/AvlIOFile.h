/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

AvlIOFile.h
This class reads/writes AVL-tree nodes on the disk.
This version stores all nodes in a single, contiguous file. */

#include <fstream>
#include "AvlNode.h"

class AvlIOFile
{
public:
	AvlIOFile(std::string);

	/*
	Allocate a new node on the hard disk, populate the given node with its ID.
	*/
	void AllocateNode(AvlNode&);

	/*
	Write the given node on the hard disk, using its internal ID.
	*/
	void WriteNode(AvlNode&);

	/*
	Read the specified node ID from the hard disk into the given node.
	*/
	void ReadNode(int, AvlNode&);

private:
	// max width, in bytes, of a single key
	const static int KEY_WIDTH = 27;

	// width, in bytes, of a node in the data file
	const static int NODE_WIDTH = KEY_WIDTH + 1 + 4 * sizeof(int);
	// key, terminating char, 4 ints (count, 2 children, BF)

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

