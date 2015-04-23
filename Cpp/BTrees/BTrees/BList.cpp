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
	if (r.n == (2 * r.T - 1))
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
		for (int j = x.n - 1; j >= i; j--)
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
		if (xi.n == (2 * xi.T - 1))
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
	z.n = z.T - 1;
	for (int j = 0; j < z.T - 1; j++)
	{
		z.keys[j] = y.keys[j + z.T];
	}
	if (!y.isLeaf)
	{
		for (int j = 0; j < z.T; j++)
		{
			z.children[j] = y.children[j + z.T];
		}
	}
	y.n = z.T - 1;

	// make room in x's children for z
	for (int j = x.n; j > i; j--)
	{
		x.children[j + 1] = x.children[j];
	}
	x.children[i + 1] = z.id;

	// make room in x for the median value
	for (int j = x.n - 1; j >= i; j--)
	{
		x.keys[j + 1] = x.keys[j];
	}
	x.keys[i] = y.keys[z.T - 1];
	++(x.n);

	// save the nodes to disk
	io.WriteNode(y);
	io.WriteNode(z);
	io.WriteNode(x);
	numDiskWrites += 3;
}

int BList::getLevelCount(int id)
{
	BNode node;
	io.ReadNode(id, node);

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
	BNode node;
	io.ReadNode(id, node);

	int count = 0;
	for (int j = 0; j < node.n; ++j)
	{
		count += node.keys[j].count;
	}

	// continue down if there are children
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
	BNode node;
	io.ReadNode(id, node);

	int count = node.n;

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
		for (int i = 0; i < node.n; ++i)
		{
			cout << node.keys[i].key << ", " << node.keys[i].count << endl;
		}
	}
	else
	{
		// always print the first child
		printNode(node.children[0]);

		// go through and print each key and the child after it
		for (int i = 0; i < node.n; ++i)
		{
			cout << node.keys[i].key << ", " << node.keys[i].count << endl;
			printNode(node.children[i + 1]);
		}
	}
}