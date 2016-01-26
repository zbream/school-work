/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BIOFolder.h
This class reads/writes B-tree nodes on the disk.
This version stores each node as a separate file on the disk. */

#include "BNode.h"

class BIOFolder
{
public:
	BIOFolder(std::string directory) : directory(directory) {}

	/*
	Allocate a new node on the hard disk, populate the given node with its ID.
	*/
	void AllocateNode(BNode&);

	/*
	Write the given node on the hard disk, using its internal ID.
	*/
	void WriteNode(BNode&);

	/*
	Read the specified node ID from the hard disk into the given node.
	*/
	void ReadNode(int, BNode&);

private:
	// io folder
	std::string directory;

	// the latest node number that has been allocated
	int latestFile = 0;
};

