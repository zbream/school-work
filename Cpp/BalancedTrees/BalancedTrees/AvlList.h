#include "WordList.h"
#include "AvlNode.h"

class AvlList :
	public WordList
{
public:
	AvlList();
	~AvlList();

	void Insert(std::string);

	int GetHeight()
	{
		return getLevelCount(root) - 1;
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
