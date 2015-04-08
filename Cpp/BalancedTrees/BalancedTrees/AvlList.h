/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

AvlList.h
This class implements the WordList using an AVL balanced tree. */

#include "WordList.h"
#include "AvlNode.h"

class AvlList :
	public WordList
{
public:
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
		return printNode(root);
	}

	int GetComparisonsMade()
	{
		return numComparisonsMade;
	}

	int GetPointerChangesMade()
	{
		return numPointerChangesMade;
	}

	int GetBFChangesMade()
	{
		return numBFChangesMade;
	}

private:
	AvlNode* root = nullptr;

	int numComparisonsMade = 0;
	int numPointerChangesMade = 0;

	int numBFChangesMade = 0;
};

