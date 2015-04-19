#pragma once
#include <string>

class WordList
{
public:
	virtual void Insert(std::string) = 0;

	virtual int GetHeight() = 0;

	virtual int GetWordCount() = 0;

	virtual int GetDistinctWordCount() = 0;
	
	virtual void PrintList() = 0;

	int GetDiskAlloc()
	{
		return numDiskAlloc;
	}

	int GetDiskReads()
	{
		return numDiskReads;
	}

	int GetDiskWrites()
	{
		return numDiskWrites;
	}

protected:
	int numDiskAlloc = 0;
	int numDiskReads = 0;
	int numDiskWrites = 0;
};