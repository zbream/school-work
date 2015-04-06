#include "WordList.h"
#include "RbNode.h"

class RbList :
	public WordList
{
public:
	RbList();
	~RbList();

	void Insert(std::string);

	int GetHeight()
	{
		return getLevelCount(root, nil);
	}

	int GetWordCount()
	{
		return getWordCount(root, nil);
	}

	int GetDistinctWordCount()
	{
		return getDistinctWordCount(root, nil);
	}

	void PrintList()
	{
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

	void fixup(RbNode*);
	void leftRotate(RbNode*);
	void rightRotate(RbNode*);
};

