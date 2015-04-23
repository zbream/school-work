#include <fstream>
#include "BIOFolder.h"

using namespace std;

void BIOFolder::AllocateNode(BNode& node)
{
	// create new node
	node.id = ++latestFile;
	node.n = 0;
	
	// create space for node
	fstream o;
	o.open(directory + to_string(node.id), ios::out);
	o.flush();
	o.close();
}

const char SEP = '\t';

void BIOFolder::WriteNode(BNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(node.id), ios::out | ios::trunc);

	// write contents of node
	f << node.isLeaf << SEP;
	f << node.n << SEP;
	for (int i = 0; i < node.n; i++)
	{
		f << node.keys[i].key << SEP << node.keys[i].count << SEP;
	}
	for (int i = 0; i < node.n + 1; i++)
	{
		f << node.children[i] << SEP;
	}

	// finish and return
	f.flush();
	f.close();
}

void BIOFolder::ReadNode(int i, BNode& node)
{
	// open the file
	fstream f;
	f.open(directory + to_string(i), ios::in);

	// read contents of node
	node.id = i;
	f >> node.isLeaf;
	f >> node.n;
	for (int i = 0; i < node.n; i++)
	{
		f >> node.keys[i].key;
		f >> node.keys[i].count;
	}
	for (int i = 0; i < node.n + 1; i++)
	{
		f >> node.children[i];
	}

	// finish and return
	f.close();
}