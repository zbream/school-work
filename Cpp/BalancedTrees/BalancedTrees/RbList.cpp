#include "RbList.h"
#include <iostream>

using namespace std;

RbList::RbList()
{
	nil = new RbNode("", true);
	nil->parent = nil->left = nil->right = nil;
	root = nil;
}


RbList::~RbList()
{
}

void RbList::Insert(string key)
{
	// start at the root
	RbNode* x = root;
	RbNode* y = nil;

	// first phase: look for the node, or where it should be
	while (x != nil)
	{
		// compare added word and current node
		int comparison = key.compare(x->key);

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
	// x==nil, y is parent of new node

	// second phase: add the word to the tree in a new node
	RbNode* newNode = new RbNode(key, false);
	newNode->parent = y;

	// if parent reference is still nil, the tree is empty
	if (y == nil)
	{
		root = newNode;
	}
	else
	{
		// put new node to left/right child of the 'y' node
		if (key < y->key)
		{
			y->left = newNode;
		}
		else
		{
			y->right = newNode;
		}
	}

	// node is at the bottom, so leaf children
	newNode->left = newNode->right = nil;

	// fix what we broke
	fixup(newNode);
}

void RbList::fixup(RbNode* z)
{
	RbNode* y;

	while (!z->parent->isBlack)
	{
		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if (!y->isBlack)
			{
				// case 1
				z->parent->isBlack = true;
				y->isBlack = true;
				z->parent->parent->isBlack = false;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					// case 2
					z = z->parent;
					leftRotate(z);
				}

				// case 3
				z->parent->isBlack = true;
				z->parent->parent->isBlack = false;
				rightRotate(z->parent->parent);
			}


		}
		else
		{
			y = z->parent->parent->left;
			if (!y->isBlack)
			{
				// case 1
				z->parent->isBlack = true;
				y->isBlack = true;
				z->parent->parent->isBlack = false;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					// case 2
					z = z->parent;
					rightRotate(z);
				}

				// case 3
				z->parent->isBlack = true;
				z->parent->parent->isBlack = false;
				leftRotate(z->parent->parent);
			}
		}
	}

	root->isBlack = true;
}

void RbList::leftRotate(RbNode* x)
{
	// y is x's right subchild
	RbNode* y = x->right;

	// move y's left subtree (beta) to x's right subtree
	x->right = y->left;

	// if (beta) is not nil, it needs its parent changed
	if (y->left != nil)
	{
		y->left->parent = x;
	}

	// y's parent is now x's old parent
	y->parent = x->parent;

	// if x was the root, y is the new root
	if (x->parent == nil)
	{
		// x was the root
		root = y;
	}
	else
	{
		// x was not the root

		// x's old parent must now point to y
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}

	// x is now left of y
	y->left = x;
	x->parent = y;
}

void RbList::rightRotate(RbNode* x)
{
	// y is x's left subchild
	RbNode* y = x->left;

	// move y's right subtree (beta) to x's left subtree
	x->left = y->right;

	// if (Beta) is not nil, it needs its parent changed
	if (y->right != nil)
	{
		y->right->parent = x;
	}

	// y's parent is now x's old parent
	y->parent = x->parent;

	// if x was the root, y is the new root
	if (x->parent == nil)
	{
		// x was the root
		root = y;
	}
	else
	{
		// x was not the root

		// x's old parent must now point to y
		if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
	}

	// x is now right of y
	y->right = x;
	x->parent = y;
}