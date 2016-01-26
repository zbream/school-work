/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BNode.h
This struct implements a BTree node.
Distinguishing factors include: number of keys n, array of Data (key/count pairs), array of children.
We do not initialize anything, because they will immediately be changed regardless.
*/

#include "Data.h"

struct BNode
{
	// T of the tree, the median key of the keys (1-based, so t>=2)
	const static int T = 2;

	// record on drive
	int id;
	
	// payload
	int n;
	Data keys[2 * T - 1];

	// children
	int children[2 * T];
	
	bool isLeaf;
};