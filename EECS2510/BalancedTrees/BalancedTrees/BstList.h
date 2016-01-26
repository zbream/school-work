/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

BstList.h
This class implements the WordList using a standard Binary Search Tree. */

#include "WordList.h"
#include "BstNode.h"

class BstList :
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

private:
	BstNode* root = nullptr;

	int numComparisonsMade = 0;
	int numPointerChangesMade = 0;
};

