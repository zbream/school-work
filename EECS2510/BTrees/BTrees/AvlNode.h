/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

AvlNode.h
This struct implements an AVL Tree node.
Distinguishing factors include: single key/count pair, two children pointers, balance factor.
We do not initialize anything, because they will immediately be changed regardless.
*/

#include <string>

struct AvlNode
{
	// record on drive
	int id;

	// payload
	std::string key;
	int count;

	// children
	int left;
	int right;

	int BF;
};