/* Ream, Zack - Lab 1 BST
EECS 2510 - 02/17/2015 */

#include "Bst.h"

Bst::Bst(){}

Bst::~Bst(){}

/*
Adds the given string into the Bst.
Outputs the count of how many times the string has been added.

ASSUME: s is not null
*/
void Bst::Insert(string key)
{
	BstNode* result = insertInternal(key);

	cout << result->Format() << endl;
}

/*
Utility function that actually inserts data for the given string into the Bst.
Adds the appropriate node where it should be (count = 1), or increments the count.

Returns the node of the string.
*/
BstNode* Bst::insertInternal(string& const key)
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
			return x;
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
		newNode->parent = y;
	}

	return newNode;
}

/*
Deletes the given string from the Bst once.
If the string has been added, outputs the new count of how many times the string has been added.
If the string has not been added, outputs -1 for the count.

ASSUME: s is not null
*/
void Bst::Delete(string key)
{
	// look for the node in the tree
	BstNode* keyNode = searchInternal(root, key);

	if (keyNode == NULL)
	{
		// the node was not found, output -1
		cout << key << " -1\n";
	}
	else
	{
		// the node was found, decrement count
		keyNode->count--;

		cout << keyNode->Format() << endl;

		// delete if count == 0
		if (keyNode->count < 1)
		{
			deleteNode(keyNode);

			delete(keyNode);
		}
	}
}

/*
Utility class that deletes the given node from the BST.

ASSUME: z is an existing node (not NULL) that is part of the BST.
*/
void Bst::deleteNode(BstNode* z)
{
	if (z->left == NULL)
	{
		// z has no left-child, z becomes z's right-child
		transplant(z, z->right);
	}
	else if (z->right == NULL)
	{
		// z has no right-child, z becomes z's left-child
		transplant(z, z->left);
	}
	else
	{
		// z has both left- and right-children

		// find z's successor
		BstNode* y = minTree(z->right);

		// if y is not z's child
		if (y->parent != z)
		{
			// y becomes y's right-child
			transplant(y, y->right);

			// z's right-child becomes y's right-child
			y->right = z->right;
			y->right->parent = y;
		}

		// z becomes y
		transplant(z, y);

		// y's left-child becomes z's left-child
		y->left = z->left;
		y->left->parent = y;
	}
}

/*
Helper function to move a subtree.
Replaces (subtree, root u) with (subtree, root v).
Does not modify v's children.
*/
void Bst::transplant(BstNode* u, BstNode* v)
{
	// if u is the root, v becomes the new root
	if (u->parent == NULL)
	{
		root = v;
	}
	else
	{
		// u must be a child of some node u->parent
		if (u == u->parent->left)
		{
			// u is a left-child, v becomes new left-child
			u->parent->left = v;
		}
		else
		{
			// u is a right-child, v becomes new right-child
			u->parent->right = v;
		}
	}

	// v's parent is now u's parent
	if (v != NULL)
	{
		v->parent = u->parent;
	}
}

/*
Searches the Bst for the given string.
Outputs how many times the string has been inserted into the Bst.

ASSUME: s is not null
*/
void Bst::Search(string key)
{
	// search for the string in the entire Bst
	BstNode* result = searchInternal(root, key);

	if (result != NULL)
	{
		cout << result->Format() << endl;
	}
	else
	{
		cout << key << " 0\n";
	}
}

/*
Utility function to retrieve the node of the specified string.
Returns node if found, NULL otherwise.
*/
BstNode* Bst::searchInternal(BstNode* node, string& const key)
{
	// check if we've fallen off the tree or found the string's node
	if (node == NULL || key == (node->key))
	{
		return node;
	}

	// move left/right, depending on the BST property
	if (key < node->key)
	{
		return searchInternal(node->left, key);
	}
	else
	{
		return searchInternal(node->right, key);
	}
}

/*
Outputs the minimum key of the entire Bst, if one exists.
Outputs an empty line, otherwise.
*/
void Bst::Min()
{
	if (root != NULL)
	{
		// there is a root, find the min of the "subtree" starting at the root
		BstNode* result = minTree(root);

		cout << result->Format() << endl;
	}
	else
	{
		// there is no root, so no min
		cout << endl;
	}
}

/*
Utility function to find the smallest node of the tree beginning at the specified node.

ASSUME: node is not null
*/
BstNode* Bst::minTree(BstNode* node)
{
	// travel down the left children until we find the absolute min
	while (node->left != NULL)
	{
		node = node->left;
	}

	return node;
}

/*
Outputs the maximum key of the entire Bst, if one exists.
Outputs an empty line, otherwise.
*/
void Bst::Max()
{
	if (root != NULL)
	{
		// there is a root, find the max of the "subtree" starting at the root
		BstNode* result = maxTree(root);

		cout << result->Format() << endl;
	}
	else
	{
		// there is no root, so no max
		cout << endl;
	}
}

/*
Utility function to find the largest node of the tree beginning at the specified node.

ASSUME: node is not null
*/
BstNode* Bst::maxTree(BstNode* node)
{
	// travel down the right children until we find the absolute max
	while (node->right != NULL)
	{
		node = node->right;
	}

	return node;
}

/*
Outputs the string that succeeds the given string in the Bst.
If the string does not exist, or there is no successor, outputs a blank line.
*/
void Bst::Next(string key)
{
	// check if string exists in tree
	BstNode* keyNode = searchInternal(root, key);

	if (keyNode != NULL)
	{
		// the string exists, get its successor
		BstNode* result = nextNode(keyNode);

		// check if successor actually exists
		if (result != NULL)
		{
			cout << result->Format() << endl;
		}
		else
		{
			cout << endl;
		}
	}
	else
	{
		// the string does not exist, print a blank line
		cout << endl;
	}
}

/*
Utility function to find the succeeding node of the given node.
Returns NULL if no succeeding node exists

ASSUME: node is not null
*/
BstNode* Bst::nextNode(BstNode* node)
{
	// check for right child
	if (node->right != NULL)
	{
		// find left-most descendent of right child
		return minTree(node->right);
	}
	else
	{
		// go up the chain of RIGHT parent-child links
		BstNode* parent = node->parent;

		while (parent != NULL && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}

		return parent;
	}
}

/*
Outputs the string that preceeds the given string in the Bst.
If the string does not exist, or there is no predecessor, outputs a blank line.
*/
void Bst::Prev(string key)
{
	// check if string exists in tree
	BstNode* keyNode = searchInternal(root, key);

	if (keyNode != NULL)
	{
		// the string exists, get its predecessor
		BstNode* result = prevNode(keyNode);

		// check of predecessor actually exists
		if (result != NULL)
		{
			cout << result->Format() << endl;
		}
		else
		{
			cout << endl;
		}
	}
	else
	{
		// the string does not exist, print a blank line
		cout << endl;
	}
}

/*
Utility function to find the predecessor node of the given node.
Returns NULL if no preceeding node exists

ASSUME: node is not null
*/
BstNode* Bst::prevNode(BstNode* node)
{
	// check for left child
	if (node->left != NULL)
	{
		// find right-most descendent of left-child
		return maxTree(node->left);
	}
	else
	{
		// go up the chain of LEFT child-parent links
		BstNode* parent = node->parent;

		while (parent != NULL && node == parent->left)
		{
			node = parent;
			parent = parent->parent;
		}

		return parent;
	}
}

/*
Performs an in-order traversal to print each node, starting from the root.
*/
void Bst::List()
{
	// listNode assumes the parameter is not NULL
	if (root != NULL)
	{
		listNode(root);
	}
	else
	{
		cout << endl;
	}
}

/*
Utility function to recursively in-order print the subtree starting with the given root node.

ASSUME: node is not null
*/
void Bst::listNode(BstNode* node)
{
	if (node->left != NULL) listNode(node->left);
	cout << node->Format() << endl;
	if (node->right != NULL) listNode(node->right);
}