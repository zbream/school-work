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
	static int getLevelCount(Node*);
	static int getWordCount(Node*);
	static int getDistinctWordCount(Node*);
	static void printNode(Node*);
};

