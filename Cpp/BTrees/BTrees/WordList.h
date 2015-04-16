#include <string>

class WordList
{
	virtual void Insert(std::string) = 0;

	virtual int GetHeight() = 0;

	virtual int GetWordCount() = 0;

	virtual int GetDistinctWordCount() = 0;

	virtual void PrintList() = 0;
};