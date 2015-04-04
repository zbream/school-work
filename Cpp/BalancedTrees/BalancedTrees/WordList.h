#include <string>

struct BstNode;

class WordList
{
public:
	virtual void Insert(std::string) = 0;

	virtual int GetHeight() = 0;
	virtual int GetWordCount() = 0;
	virtual int GetDistinctWordCount() = 0;
	virtual void PrintList() = 0;

protected:
	static int getLevelCount(BstNode*);
	static int getWordCount(BstNode*);
	static int getDistinctWordCount(BstNode*);
	static void printNode(BstNode*);
};

