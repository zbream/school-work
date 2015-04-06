#include "AvlList.h"

using namespace std;

AvlList::AvlList()
{
}


AvlList::~AvlList()
{
}

void AvlList::Insert(string X)
{
	// check for empty tree
	if (root == NULL)
	{
		root = new AvlNode(X);
		return;
	}

	// begin searching for where to put the new node

	// P scans until it falls off the bottom (Q is its parent)
	AvlNode *P, *Q;

	// A is the last parent with BF=+-1 (F is ITS parent)
	AvlNode *A, *F;
	
	// start at the root
	F = Q = NULL;
	A = P = root;

	// search until P falls off the tree
	while (P != NULL)
	{
		// check if we found the string
		if (X == P->key)
		{
			++(P->count);
			return;
		}

		// store the most recent BF=+-1
		if (P->BF != 0)
		{
			A = P;
			F = Q;
		}
		
		// move down, following BST property
		Q = P;
		P = (X < P->key) ? P->left : P->right;
	}
	// P==null, Q is parent of new node

	// hang the new node on the tree
	AvlNode *Y = new AvlNode(X);
	if (X < Q->key)
	{
		Q->left = Y;
	}
	else
	{
		Q->right = Y;
	}

	// now we adjust and fix imbalance

	// adjust from A to Q (A was the last one with +-1)	
	// used to check for imbalance at A
	int d;
	AvlNode *B;

	// see which subtree of A the new node went in
	if (X > A->key)
	{
		// right subtree
		P = A->right;
		B = P;

		// if A's BF was -1, we fixed its imbalance (checked later)
		d = -1;
	}
	else
	{
		// left subtree
		P = A->left;
		B = P;

		// if A's BF was +1, we fixed its imbalance (checked later)
		d = 1;
	}

	// go down and adjust BF along the tree from A's child
	while (P != Y)
	{
		// check where imbalance at the current node is
		if (X > P->key)
		{
			// new node is in right subtree, BF of -1
			P->BF = -1;
			P = P->right;
		}
		else
		{
			// new node is in left subtree, BF of +1
			P->BF = 1;
			P = P->left;
		}
	}

	// check imbalance at A
	if (A->BF == 0)
	{
		// tree was balanced, and is now acceptably imbalanced
		A->BF = d;
		return;
	}

	if (A->BF == -d)
	{
		// tree was imbalanced the other way, and is now balanced
		A->BF = 0;
		return;
	}

	// here, the tree WAS imbalanced and is now unacceptably imbalanced	
	AvlNode *C, *CL, *CR;
	
	// find necessary rotation type, perform
	if (d == 1)
	{
		// left imbalance

		if (B->BF == 1)
		{
			// LL
			A->left = B->right;
			B->right = A;
			A->BF = B->BF = 0;
		}
		else
		{
			// LR
			C = B->right;
			CL = C->left;
			CR = C->right;
						
			// change structure
			B->right = CL;
			A->left = CR;
			C->left = B;
			C->right = A;

			// change balance factors
			switch (C->BF)
			{
			case 0:
				// LR(a)
				A->BF = 0;
				B->BF = 0;
				break;
			case 1:
				// LR(b)
				A->BF = -1;
				B->BF = 0;
				break;
			case -1:
				// LR(c)
				A->BF = 0;
				B->BF = 1;
				break;
			}

			C->BF = 0;
			B = C;
		}
	}
	else
	{
		// right imbalance
		
		if (B->BF == -1)
		{
			// RR
			A->right = B->left;
			B->left = A;
			A->BF = B->BF = 0;
		}
		else
		{
			// RL
			C = B->left;
			CL = C->left;
			CR = C->right;

			// change structure
			B->left = CR;
			A->right = CL;
			C->right = B;
			C->left = A;

			// change balance factors
			switch (C->BF)
			{
			case 0:
				// RL(a)
				A->BF = 0;
				B->BF = 0;
				break;
			case -1:
				// RL(b)
				A->BF = 1;
				B->BF = 0;
				break;
			case 1:
				// RL(c)
				A->BF = 0;
				B->BF = -1;
				break;
			}

			C->BF = 0;
			B = C;
		}
	}

	// finish up: B subtree was rebalanced and is a subtree of F (which originally had root A)

	if (F == NULL)
	{
		// root was rebalanced
		root = B;
		return;
	}

	// the child of F was rebalanced
	if (A == F->left)
	{
		// F's left child
		F->left = B;
		return;
	}
	if (A == F->right)
	{
		// F's right child
		F->right = B;
		return;
	}

	// we should never be here
}