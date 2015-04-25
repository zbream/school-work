/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

AvlList.h
This class implements the WordList using an AVL balanced tree. */

#include "WordList.h"
#include "AvlIOFile.h"

class AvlList :
	public WordList
{
public:
	// initialize the IO using the given path
	AvlList(std::string datapath) : io(datapath) {}

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
	AvlIOFile io;
	
	/*
	Recursively finds the level count of the AVL tree, given its root.
	*/
	int getLevelCount(int);

	/*
	Recursively finds the total of the counts of the AVL tree, given its root.
	*/
	int getWordCount(int);

	/*
	Recursively finds the total number of words in the AVL tree, given its root.
	*/
	int getDistinctWordCount(int);

	/*
	Print to console the contents of the AVL tree, given its root.
	*/
	void printNode(int);
};

