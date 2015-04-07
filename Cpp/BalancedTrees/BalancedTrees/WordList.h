/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

WordList.h
This class acts as a generic word list to determine stats about inserted words.
Child classes will implement ways to gather metrics about the internal binary tree.
Includes static methods that will determine metrics of a generic binary tree (given its root Node). */

#pragma once
#include <string>

// prototypes
struct Node;

class WordList
{
public:
	/*
	Insert the given word into the WordList.
	If the word is not found in the list, add it.
	If the word is found in the list, increment its count;
	*/
	virtual void Insert(std::string) = 0;

	/*
	Return the height of the internal binary tree (max path from root to leaf).
	A root-only tree is height 0.
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

protected:
	/*
	Find the level count of a binary tree of generic Nodes.
	First parameter is the root of a tree.
	Second parameter terminates a path from root to leaf (usually NULL).
	*/
	static int getLevelCount(Node*, Node* = nullptr);

	/*
	Find the total of the counts of a binary tree of generic Nodes.
	First parameter is the root of a tree.
	Second parameter terminates a path from root to leaf (usually NULL).
	*/
	static int getWordCount(Node*, Node* = nullptr);

	/*
	Find the total number of words in a binary tree of generic Nodes.
	First parameter is the root of a tree.
	Second parameter terminates a path from root to leaf (usually NULL).
	*/
	static int getDistinctWordCount(Node*, Node* = nullptr);
	
	/*
	Print to console the contents of a binary tree of generic Nodes.
	First parameter is the root of a tree.
	Second parameter terminates a path from root to leaf (usually NULL).
	*/
	static void printNode(Node*, Node* = nullptr);
};

