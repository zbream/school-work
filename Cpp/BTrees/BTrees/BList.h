/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

BList.h
This class implements the WordList using a B-tree. */

#include "WordList.h"
#include "BIOFile.h"

class BList :
	public WordList
{
public:
	BList(std::string datapath);

	void Insert(std::string);

	int GetHeight()
	{
		return getLevelCount(root);
	}

	int GetWordCount()
	{
		return getWordCount(root);
	}

	int GetDistinctWordCount()
	{
		return getDistinctWordCount(root);
	}

	void PrintList()
	{
		printNode(root);
	}

private:
	int root = 0;

	// reads/writes nodes from/to the disk
	BIOFile io;
	
	/*
	Insert the given string into the given node, assuming the given node is not full.
	Moves down the tree as needed, splitting children as needed.
	*/
	void insertNonFull(BNode&, std::string&);

	/*
	Split the given child (Y) into nodes (Y) and (Z), moving the median up to (X).
	First parameter is node (X).
	Second parameter is the child of (X) that is (Y).
	Third parameter is node (Y).
	*/
	void splitChild(BNode&, int, BNode&);
	
	/*
	Recursively finds the level count of the B-tree, given its root.
	*/
	int getLevelCount(int);

	/*
	Recursively finds the total of the counts of the B-tree, given its root.
	*/
	int getWordCount(int);

	/*
	Recursively finds the total number of words in the B-tree, given its root.
	*/
	int getDistinctWordCount(int);

	/*
	Print to console the contents of the B-tree, given its root.
	*/
	void printNode(int);
};

