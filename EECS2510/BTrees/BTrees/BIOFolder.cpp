/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BIOFolder.cpp
This class reads/writes B-tree nodes on the disk.
This version stores each node as a separate file on the disk. */

#include <fstream>
#include "BIOFolder.h"

using namespace std;

void BIOFolder::AllocateNode(BNode& node)
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

void BIOFolder::WriteNode(BNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(node.id), ios::out | ios::trunc);

	// write contents of node
	f << node.isLeaf << SEP;
	f << node.n << SEP;
	for (int j = 0; j < node.n; ++j)
	{
		f << node.keys[j].key << SEP << node.keys[j].count << SEP;
	}
	for (int j = 0; j < node.n + 1; ++j)
	{
		f << node.children[j] << SEP;
	}

	// finish and return
	f.flush();
	f.close();
}

void BIOFolder::ReadNode(int id, BNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(id), ios::in);

	// read contents of node
	node.id = id;
	f >> node.isLeaf;
	f >> node.n;
	for (int j = 0; j < node.n; ++j)
	{
		f >> node.keys[j].key;
		f >> node.keys[j].count;
	}
	for (int j = 0; j < node.n + 1; ++j)
	{
		f >> node.children[j];
	}

	// finish and return
	f.close();
}