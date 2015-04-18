#include <iostream>
#include "AvlList.h"

using namespace std;

void AvlList::Insert(string X)
{
	// check for empty tree
	if (root == 0)
	{
		// create the root node
		AvlNode node;
		io.AllocateNode(node);
		++numDiskAlloc;
		node.key = X;
		node.count = 1;
		node.left = node.right = 0;
		node.BF = 0;

		// save it
		root = node.id;
		io.WriteNode(node, root);
		++numDiskWrites;

		return;
	}

	// begin searching for where to put the new node

	// P scans until it falls off the bottom (Q is its parent)
	int PI, QI;
	AvlNode P;

	// A is the last parent with BF=+-1 (F is ITS parent)
	int AI, FI;

	// start at the root
	FI = QI = 0;
	AI = PI = root;

	// search until P falls off the tree
	while (PI != 0)
	{
		// read node P
		io.ReadNode(PI, P);
		++numDiskReads;

		// compare added word and current node
		int comparison = X.compare(P.key);

		if (comparison == 0)
		{
			++(P.count);
			io.WriteNode(P, P.id);
			++numDiskWrites;
			return;
		}

		// store the most recent BF=+-1
		if (P.BF != 0)
		{
			AI = PI;
			FI = QI;
		}

		// move down, following BST property
		QI = PI;
		PI = (comparison < 0) ? P.left : P.right;
	}
	// P==null, Q is parent of new node

	// create the new node
	AvlNode Y;
	io.AllocateNode(Y);
	++numDiskAlloc;
	Y.key = X;
	Y.count = 1;
	Y.left = Y.right = 0;
	Y.BF = 0;
	io.WriteNode(Y, Y.id);
	++numDiskWrites;

	// set Y as Q's child
	AvlNode Q;
	io.ReadNode(QI, Q);
	++numDiskReads;
	if (X < Q.key)
	{
		Q.left = Y.id;
	}
	else
	{
		Q.right = Y.id;
	}
	io.WriteNode(Q, Q.id);
	++numDiskWrites;

	// now we adjust and fix imbalance

	// adjust from A to Q (A was the last one with +-1)
	// used to check for imbalance at A
	int d;
	int BI;

	// see which subtree of A the new node went in
	AvlNode A;
	io.ReadNode(AI, A);
	if (X > A.key)
	{
		// right subtree
		io.ReadNode(A.right, P);

		BI = P.id;

		// if A's BF was -1, we fixed its imbalance (checked later)
		d = -1;
	}
	else
	{
		// left subtree
		io.ReadNode(A.left, P);
		BI = P.id;

		//  if A's BF was +1, we fixed its imbalance (checked later)
		d = 1;
	}
	numDiskReads += 2;

	// go down and adjust BF along the tree from A's child
	while (P.id != Y.id)
	{
		// check where imbalance at the current node is
		if (X > P.key)
		{
			// new node is in right subtree, BF of -1
			P.BF = -1;
			io.WriteNode(P, P.id);

			io.ReadNode(P.right, P);
		}
		else
		{
			// new node is in left subtree, BF of +1
			P.BF = 1;
			io.WriteNode(P, P.id);

			io.ReadNode(P.left, P);
		}
		++numDiskReads;
		++numDiskWrites;
	}

	// check imbalance at A
	if (A.BF == 0)
	{
		// tree was balanced, and is now acceptably imbalanced
		A.BF = d;
		io.WriteNode(A, A.id);
		++numDiskWrites;
		return;
	}

	if (A.BF == -d)
	{
		A.BF = 0;
		io.WriteNode(A, A.id);
		++numDiskWrites;
		return;
	}

	// here, the tree WAS imbalanced and is now unacceptably imbalanced
	AvlNode B;
	io.ReadNode(BI, B);
	++numDiskReads;
	AvlNode C;

	// find necessary rotation type, perform
	if (d == 1)
	{
		// left imbalance

		if (B.BF == 1)
		{
			// LL
			A.left = B.right;
			B.right = A.id;

			A.BF = B.BF = 0;

			io.WriteNode(A, A.id);
			io.WriteNode(B, B.id);
			numDiskWrites += 2;
		}
		else
		{
			// LR
			io.ReadNode(B.right, C);
			++numDiskReads;

			// change structure
			B.right = C.left;
			A.left = C.right;
			C.left = B.id;
			C.right = A.id;

			// change balance factors
			switch (C.BF)
			{
			case 0:
				// LR(a)
				A.BF = 0;
				B.BF = 0;
				break;
			case 1:
				// LR(b)
				A.BF = -1;
				B.BF = 0;
				break;
			case -1:
				// LR(c)
				A.BF = 0;
				B.BF = 1;
				break;
			}
			C.BF = 0;
			io.WriteNode(A, A.id);
			io.WriteNode(B, B.id);
			io.WriteNode(C, C.id);
			numDiskWrites += 3;

			B = C;
		}
	}
	else
	{
		// right imbalance

		if (B.BF == -1)
		{
			// RR
			A.right = B.left;
			B.left = A.id;

			A.BF = B.BF = 0;

			io.WriteNode(A, A.id);
			io.WriteNode(B, B.id);
			numDiskWrites += 2;
		}
		else
		{
			// RL
			io.ReadNode(B.left, C);
			++numDiskReads;

			// change structure
			B.left = C.right;
			A.right = C.left;
			C.right = B.id;
			C.left = A.id;

			// change balance factors
			switch (C.BF)
			{
			case 0:
				// RL(a)
				A.BF = 0;
				B.BF = 0;
				break;
			case -1:
				// RL(b)
				A.BF = 1;
				B.BF = 0;
				break;
			case 1:
				// RL(c)
				A.BF = 0;
				B.BF = -1;
				break;
			}
			C.BF = 0;
			io.WriteNode(A, A.id);
			io.WriteNode(B, B.id);
			io.WriteNode(C, C.id);
			numDiskWrites += 3;

			B = C;
		}
	}

	// finish up: B subtree was rebalanced and is a subtree of F (which originally had root A)

	if (FI == 0)
	{
		// root was rebalanced
		root = B.id;
		return;
	}

	// the child of F was rebalanced
	AvlNode F;
	io.ReadNode(FI, F);
	++numDiskReads;
	if (A.id == F.left)
	{
		// F's left child
		F.left = B.id;
		io.WriteNode(F, F.id);
		++numDiskWrites;
		return;
	}
	if (A.id == F.right)
	{
		// F's right child
		F.right = B.id;
		io.WriteNode(F, F.id);
		++numDiskWrites;
		return;
	}

	// we should never be here
}

int AvlList::getLevelCount(int id)
{
	if (id == 0)
	{
		return 0;
	}
	AvlNode node;
	io.ReadNode(id, node);

	// find the maximum path from here down
	int heightL = getLevelCount(node.left);
	int heightR = getLevelCount(node.right);

	int maxHeight = (heightL > heightR ? heightL : heightR);

	return (1 + maxHeight);
}

int AvlList::getWordCount(int id)
{
	if (id == 0)
	{
		return 0;
	}
	AvlNode node;
	io.ReadNode(id, node);

	return (node.count + getWordCount(node.left) + getWordCount(node.right));
}

int AvlList::getDistinctWordCount(int id)
{
	if (id == 0)
	{
		return 0;
	}
	AvlNode node;
	io.ReadNode(id, node);

	return (1 + getDistinctWordCount(node.left) + getDistinctWordCount(node.right));
}

void AvlList::printNode(int id)
{
	if (id == 0)
	{
		return;
	}
	AvlNode node;
	io.ReadNode(id, node);

	printNode(node.left);
	cout << node.key << ", " << node.count << "\n";
	printNode(node.right);
}
