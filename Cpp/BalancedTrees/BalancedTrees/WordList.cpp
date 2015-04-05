#include <iostream>
#include "WordList.h"
#include "BstNode.h"

using namespace std;

int WordList::getLevelCount(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	int heightL = getLevelCount(node->GetLeft());
	int heightR = getLevelCount(node->GetRight());

	int maxHeight = (heightL > heightR ? heightL : heightR);

	return (1 + maxHeight);
}

int WordList::getWordCount(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	return (node->count + getWordCount(node->GetLeft()) + getWordCount(node->GetRight()));
}

int WordList::getDistinctWordCount(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	return (1 + getDistinctWordCount(node->GetLeft()) + getDistinctWordCount(node->GetRight()));
}

void WordList::printNode(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	printNode(node->GetLeft());
	cout << node->key << ", " << node->count << endl;
	printNode(node->GetRight());
}