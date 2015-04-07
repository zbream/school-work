/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

WordList.cpp
This class acts as a generic word list to determine stats about inserted words.
Child classes will implement ways to gather metrics about the internal binary tree.
Includes static methods that will determine metrics of a generic binary tree (given its root Node). */

#include <iostream>
#include "WordList.h"
#include "BstNode.h"

using namespace std;

int WordList::getLevelCount(Node* node, Node* empty)
{
	if (node == empty)
	{
		return 0;
	}

	// find the maximum path from here down
	int heightL = getLevelCount(node->GetLeft(), empty);
	int heightR = getLevelCount(node->GetRight(), empty);

	int maxHeight = (heightL > heightR ? heightL : heightR);

	return (1 + maxHeight);
}

int WordList::getWordCount(Node* node, Node* empty)
{
	if (node == empty)
	{
		return 0;
	}

	return (node->count + getWordCount(node->GetLeft(), empty) + getWordCount(node->GetRight(), empty));
}

int WordList::getDistinctWordCount(Node* node, Node* empty)
{
	if (node == empty)
	{
		return 0;
	}

	return (1 + getDistinctWordCount(node->GetLeft(), empty) + getDistinctWordCount(node->GetRight(), empty));
}

void WordList::printNode(Node* node, Node* empty)
{
	if (node == empty)
	{
		return;
	}

	printNode(node->GetLeft(), empty);
	cout << node->key << ", " << node->count << endl;
	printNode(node->GetRight(), empty);
}