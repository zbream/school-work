#include "WordList.h"
#include "AvlNode.h"

class AvlList :
	public WordList
{
public:
	void Insert(std::string);

	int GetHeight();

	int GetWordCount();

	int GetDistinctWordCount();

	void PrintList();
};

