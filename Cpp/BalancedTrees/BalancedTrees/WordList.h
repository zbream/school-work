#pragma once
#include <string>

struct Node;

class WordList
{
public:
	virtual void Insert(std::string) = 0;

	virtual int GetHeight() = 0;
	virtual int GetWordCount() = 0;
	virtual int GetDistinctWordCount() = 0;
	virtual void PrintList() = 0;

protected:
	static int getLevelCount(Node*, Node* = nullptr);
	static int getWordCount(Node*, Node* = nullptr);
	static int getDistinctWordCount(Node*, Node* = nullptr);
	static void printNode(Node*, Node* = nullptr);
};

