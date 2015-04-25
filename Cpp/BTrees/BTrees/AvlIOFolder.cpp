/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

AvlIOFolder.cpp
This class reads/writes AVL-tree nodes on the disk.
This version stores each node as a separate file on the disk. */

#include <fstream>
#include "AvlIOFolder.h"

using namespace std;

void AvlIOFolder::AllocateNode(AvlNode& node)
{
	// create new node
	node.id = ++latestFile;

	// create space for node
	fstream o;
	o.open(directory + to_string(node.id), ios::out);
	o.flush();
	o.close();
}

// the separator between records in each file
const char SEP = '\t';

void AvlIOFolder::WriteNode(AvlNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(node.id), ios::out | ios::trunc);

	// write contents of node
	f << node.key << SEP;
	f << node.count << SEP;
	f << node.left << SEP;
	f << node.right << SEP;
	f << node.BF << SEP;

	// finish and return
	f.flush();
	f.close();
}

void AvlIOFolder::ReadNode(int id, AvlNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(id), ios::in);

	// read contents of node
	node.id = id;
	f >> node.key;
	f >> node.count;
	f >> node.left;
	f >> node.right;
	f >> node.BF;
	
	// finish and return
	f.close();
}