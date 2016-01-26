/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

WordList.h
This class acts as a generic word list to determine stats about inserted words.
Child classes will implement ways to gather metics about the internal tree. */

#pragma once
#include <string>

class WordList
{
public:
	/*
	Insert the given word into the WordList.
	If the word is not found in the list, add it.
	IF the word is found in the list, increment its count.
	*/
	virtual void Insert(std::string) = 0;

	/*
	Return the height of the internal tree (max path from root to leaf).
	*/
	virtual int GetHeight() = 0;

	/*
	Return the number of words added to the list (total of the counts).
	*/
	virtual int GetWordCount() = 0;

	/*
	Return the number of distinct words added to the list.
	*/
	virtual int GetDistinctWordCount() = 0;
	
	/*
	Write the contents of the list, in alphabetical order, to console.
	*/
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