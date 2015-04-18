#include <fstream>
#include "AvlIOFolder.h"

using namespace std;

void AvlIOFolder::AllocateNode(AvlNode& node)
{
	// create new node
	node.id = ++latestFile;
	node.key = "";
	node.count = 0;
	node.left = 0;
	node.right = 0;
	node.BF = 0;

	// create space for node
	fstream o;
	o.open(directory + to_string(node.id), ios::out);
	o.flush();
	o.close();
}

const char SEP = '\t';

void AvlIOFolder::WriteNode(AvlNode& node, int i)
{
	// check if node has been allocated
	if (i > latestFile)
	{
		exit(1);
	}

	// open the file
	fstream f;
	f.open(directory + to_string(i), ios::out | ios::trunc);

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

void AvlIOFolder::ReadNode(int i, AvlNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(i), ios::in);

	// read contents of node
	node.id = i;
	f >> node.key;
	f >> node.count;
	f >> node.left;
	f >> node.right;
	f >> node.BF;
	
	// finish and return
	f.close();
}