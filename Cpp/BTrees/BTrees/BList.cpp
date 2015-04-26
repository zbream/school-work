/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BList.cpp
This class implements the WordList using a B-tree. */

#include <iostream>
#include "BList.h"

using namespace std;

BList::BList(string datapath) : io(datapath)
{
	// create empty root node
	BNode r;
	io.AllocateNode(r);
	r.isLeaf = true;
	r.n = 0;
	io.WriteNode(r);
	
	root = r.id;

	// metrics
	++numDiskAlloc;
	++numDiskWrites;
}

void BList::Insert(string k)
{
	// get the node
	BNode r;
	io.ReadNode(root, r);
	++numDiskReads;

	// check if the root node is full
	if (r.n == (2 * BNode::T - 1))
	{
		// root is full, split it

		// create new root, old root is its child0
		BNode s;
		io.AllocateNode(s);
		++numDiskAlloc;
		root = s.id;
		s.isLeaf = false;
		s.n = 0;
		s.children[0] = r.id;
		splitChild(s, 0, r);

		// insert using new root
		insertNonFull(s, k);
	}
	else
	{
		insertNonFull(r, k);
	}
}

void BList::insertNonFull(BNode& x, std::string& k)
{
	// find position where the key ought to be
	int i = x.n - 1;
	while (i >= 0 && k < x.keys[i].key)
	{
		--i;
	}
	
	// check if we found the key
	if (i >= 0 && k == x.keys[i].key)
	{
		// just increment the key's count'
		++(x.keys[i].count);
		io.WriteNode(x);
		++numDiskWrites;
		return;
	}
	// the key was not found, insert as new
	++i;
		
	if (x.isLeaf)
	{
		// leaf, so add key to this node

		// make space for the key
		for (int j = x.n - 1; j >= i; --j)
		{
			x.keys[j + 1] = x.keys[j];
		}

		// insert the new key
		x.keys[i].key = k;
		x.keys[i].count = 1;
		++(x.n);
		io.WriteNode(x);
		++numDiskWrites;
	}
	else
	{
		// not a leaf, so key goes further down the tree
		
		// check the child node
		BNode xi;
		io.ReadNode(x.children[i], xi);
		++numDiskReads;
		
		// if child is full, go ahead and preemptively split it
		if (xi.n == (2 * BNode::T - 1))
		{
			splitChild(x, i, xi);

			// there is a chance that this split pulled our k up as the median value
			if (k == x.keys[i].key)
			{
				// just increment the key's count'
				++(x.keys[i].count);
				io.WriteNode(x);
				++numDiskWrites;
				return;
			}

			// split may have changed which child we follow
			if (k > x.keys[i].key)
			{
				io.ReadNode(x.children[i + 1], xi);
				++numDiskReads;
			}
		}

		// move execution down to child node
		insertNonFull(xi, k);
	}
}

void BList::splitChild(BNode& x, int i, BNode& y)
{
	// create new child of x (sibling of y)
	BNode z;
	io.AllocateNode(z);
	++numDiskAlloc;
	z.isLeaf = y.isLeaf;

	// z gets the right "section" of keys/children from y
	z.n = BNode::T - 1;
	for (int j = 0; j < BNode::T - 1; ++j)
	{
		z.keys[j] = y.keys[j + BNode::T];
	}
	if (!y.isLeaf)
	{
		for (int j = 0; j < BNode::T; ++j)
		{
			z.children[j] = y.children[j + BNode::T];
		}
	}
	y.n = BNode::T - 1;

	// make room in x's children for z
	for (int j = x.n; j > i; --j)
	{
		x.children[j + 1] = x.children[j];
	}
	x.children[i + 1] = z.id;

	// make room in x for the median value
	for (int j = x.n - 1; j >= i; --j)
	{
		x.keys[j + 1] = x.keys[j];
	}
	x.keys[i] = y.keys[BNode::T - 1];
	++(x.n);

	// save the nodes to disk
	io.WriteNode(y);
	io.WriteNode(z);
	io.WriteNode(x);
	numDiskWrites += 3;
}

int BList::getLevelCount(int id)
{
	// the tree is perfectly balanced, so any path down is sufficient.

	BNode node;
	io.ReadNode(id, node);

	// continue if there are children
	if (node.isLeaf)
	{
		return 1;
	}
	else
	{
		return(1 + getLevelCount(node.children[0]));
	}
}

int BList::getWordCount(int id)
{
	// go through and add the counts of each key

	BNode node;
	io.ReadNode(id, node);

	// count the total words
	int count = 0;
	for (int j = 0; j < node.n; ++j)
	{
		count += node.keys[j].count;
	}

	// continue if there are children
	if (!node.isLeaf)
	{
		for (int j = 0; j <= node.n; ++j)
		{
			count += getWordCount(node.children[j]);
		}
	}

	return count;
}

int BList::getDistinctWordCount(int id)
{
	// add the n's (number of keys) of each node

	BNode node;
	io.ReadNode(id, node);

	// n is the total number of distinct words
	int count = node.n;

	// continue if there are children
	if (!node.isLeaf)
	{
		for (int j = 0; j < node.n + 1; ++j)
		{
			count += getDistinctWordCount(node.children[j]);
		}
	}

	return count;
}

void BList::printNode(int id)
{
	BNode node;
	io.ReadNode(id, node);

	if (node.isLeaf)
	{
		// only print the keys in this node
		for (int j = 0; j < node.n; ++j)
		{
			cout << node.keys[j].key << ", " << node.keys[j].count << endl;
		}
	}
	else
	{
		// always print the first child
		printNode(node.children[0]);

		// go through and print each key and the child after it
		for (int j = 0; j < node.n; ++j)
		{
			cout << node.keys[j].key << ", " << node.keys[j].count << endl;
			printNode(node.children[j + 1]);
		}
	}
}