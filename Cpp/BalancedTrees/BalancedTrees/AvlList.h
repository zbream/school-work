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
		return comparisonsMade;
	}

	int GetPointerChangesMade()
	{
		return pointerChangesMade;
	}

private:
	AvlNode* root = nullptr;

	int comparisonsMade = 0;
	int pointerChangesMade = 0;
};

