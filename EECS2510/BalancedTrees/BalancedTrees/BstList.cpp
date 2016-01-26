/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

BstList.cpp
This class implements the WordList using a standard Binary Search Tree. */

#include "BstList.h"

using namespace std;

void BstList::Insert(string key)
{
	// start at the root
	BstNode* x = root;
	BstNode* y = NULL;

	// first phase: look for the node, or where it should be
	while (x != NULL)
	{
		// compare added word and current node
		int comparison = key.compare(x->key);
		++numComparisonsMade;

		if (comparison == 0)
		{
			// node is a match
			++(x->count);
			return;
		}

		// move down, following BST property
		y = x;
		x = (comparison < 0 ? x->left : x->right);
	}
	// x==null, y is parent of new node

	// second phase: add the word to the tree in a new node
	BstNode* newNode = new BstNode(key);

	// if parent reference is STILL null, the tree is empty; create root
	if (y == NULL)
	{
		root = newNode;
	}
	else
	{
		// put new node to left/right child of the 'y' node
		++numComparisonsMade;
		if (key < y->key)
		{
			y->left = newNode;
		}
		else
		{
			y->right = newNode;
		}
	}
	
	// root reassign is also a pointer change
	++numPointerChangesMade;
}