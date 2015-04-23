#include "WordList.h"
#include "AvlIOFolder.h"

class AvlList :
	public WordList
{
public:
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
		
	AvlIOFolder io;

	int getLevelCount(int);
	int getWordCount(int);
	int getDistinctWordCount(int);
	void printNode(int);
};

