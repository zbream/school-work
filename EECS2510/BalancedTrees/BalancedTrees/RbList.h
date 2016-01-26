/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

RbList.h
This class implements the WordList using a Red-Black balanced tree. */

#include "WordList.h"
#include "RbNode.h"

class RbList :
	public WordList
{
public:
	RbList();

	void Insert(std::string);

	int GetHeight()
	{
		// traverse to NIL leaf
		return getLevelCount(root, nil);
	}

	int GetWordCount()
	{
		// traverse to NIL leaf
		return getWordCount(root, nil);
	}

	int GetDistinctWordCount()
	{
		// traverse to NIL leaf
		return getDistinctWordCount(root, nil);
	}

	void PrintList()
	{
		// traverse to NIL leaf
		return printNode(root, nil);
	}

	int GetComparisonsMade()
	{
		return numComparisonsMade;
	}

	int GetPointerChangesMade()
	{
		return numPointerChangesMade;
	}

	int GetRecoloringsMade()
	{
		return numRecoloringsMade;
	}

private:
	RbNode *root, *nil;

	int numComparisonsMade = 0;
	int numPointerChangesMade = 0;

	int numRecoloringsMade = 0;

	/*
	Perform an Insert-Fixup on the given new node Z.
	*/
	void fixup(RbNode*);

	/*
	Perform a Left-Rotate on the given X node.
	*/
	void leftRotate(RbNode*);

	/*
	Perform a Right-Rotate on the given X node.
	*/
	void rightRotate(RbNode*);
};

