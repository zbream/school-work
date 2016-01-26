/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

AvlIOFolder.h
This class reads/writes AVL-tree nodes on the disk.
This version stores each node as a separate file on the disk. */

#include "AvlNode.h"

class AvlIOFolder
{
public:
	AvlIOFolder(std::string directory) : directory(directory) {}

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
	// io folder
	std::string directory;

	// the latest node number that has been allocated
	int latestFile = 0;
};

