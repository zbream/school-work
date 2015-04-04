#include <iostream>
#include "WordList.h"
#include "BstNode.h"

using namespace std;

int WordList::getLevelCount(BstNode* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	int heightL = getLevelCount(node->left);
	int heightR = getLevelCount(node->right);

	int maxHeight = (heightL > heightR ? heightL : heightR);

	return (1 + maxHeight);
}

int WordList::getWordCount(BstNode* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	return (node->count + getWordCount(node->left) + getWordCount(node->right));
}

int WordList::getDistinctWordCount(BstNode* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	return (1 + getDistinctWordCount(node->left) + getDistinctWordCount(node->right));
}

void WordList::printNode(BstNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	printNode(node->left);
	cout << node->key << ", " << node->count << endl;
	printNode(node->right);
}