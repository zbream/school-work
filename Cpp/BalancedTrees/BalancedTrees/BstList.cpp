#include "BstList.h"
#include "BstNode.h"

using namespace std;

BstList::BstList()
{
}


BstList::~BstList()
{
}

void BstList::Insert(string key)
{
	// start at the root
	BstNode* x = root;
	BstNode* y = NULL;

	// first phase, look for the node, or where it should be
	while (x != NULL)
	{
		// move 'x' node to parent reference 'y'
		y = x;

		// compare added word and current node
		int comparison = key.compare(x->key);

		// if the node is a match, increment its count and return
		// if not, move left or right
		if (comparison == 0)
		{
			x->count++;
			return;
		}
		else
		{
			if (comparison < 0)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}
	}
	// at this point, x==null, y holds the parent of the new node

	// second phase: add the word to the tree in a new node
	BstNode* newNode = new BstNode(key);

	// if parent reference is STILL null, the tree is empty; create root
	if (y == NULL)
	{
		root = newNode;
	}
	else
	{
		// put new node to left/right child of the 'y'node
		if (key < y->key)
		{
			y->left = newNode;
		}
		else
		{
			y->right = newNode;
		}
	}
}