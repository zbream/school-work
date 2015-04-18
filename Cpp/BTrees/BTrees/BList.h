#include "WordList.h"
#include "BIOFolder.h"

class BList :
	public WordList
{
public:
	BList() : io("D:\\Zack\\Desktop\\Files\\") {}

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

	BIOFolder io;

	int getLevelCount(int);
	int getWordCount(int);
	int getDistinctWordCount(int);
	void printNode(int);
};

