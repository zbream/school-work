/* Ream, Zack - Lab 1 BST
EECS 2510 - 02/17/2015 */

#include <iostream>
#include <string>

using namespace std;

/*
Represents a single node of the binary-tree.
Contains fields for a key and count.
*/
struct BstNode
{
	string key;
	int count;
	BstNode *left = NULL;
	BstNode *right = NULL;
	BstNode *parent = NULL;

	// obviously, if a string is just being found and created, it has been found once
	BstNode(string k) : key(k), count(1) {}

	// returns string "<key> <count>" that the interface returns to the user
	string Format()
	{
		return key + " " + to_string(count);
	}
};

/*
Represents all functionality of a binary-search-tree.
*/
class Bst
{
public:
	Bst();
	~Bst();

	void Insert(string);
	void Delete(string);
	void Search(string);
	void Min();
	void Max();
	void Next(string);
	void Prev(string);
	void List();

private:
	// reference to root of the tree
	BstNode* root = NULL;

	// all helper/utility functionality
	BstNode* insertInternal(string& const);
	void deleteNode(BstNode*);
	void transplant(BstNode*, BstNode*);
	static BstNode* searchInternal(BstNode*, string& const);
	static BstNode* minTree(BstNode*);
	static BstNode* maxTree(BstNode*);
	static BstNode* nextNode(BstNode*);
	static BstNode* prevNode(BstNode*);
	static void listNode(BstNode*);
};

