#include "WordList.h"
#include "BstNode.h"

class BstList :
	public WordList
{
public:
	BstList();
	~BstList();

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

private:
	BstNode* root = nullptr;

	int numComparisonsMade = 0;
	int numPointerChangesMade = 0;
};

