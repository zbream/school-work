#include <iostream>
#include "BstList.h"
#include "AvlList.h"
#include "RbList.h"

using namespace std;

void TestNumbers(WordList&);

int main()
{
	BstList bstList = BstList();
	AvlList avlList = AvlList();
	RbList rbList = RbList();

	//TestNumbers(bstList);
	TestNumbers(avlList);
	TestNumbers(rbList);

	cout << "done";
	cin.get();
}

void TestNumbers(WordList& list)
{
	char chari[10];
	for (int i = 0; i < 10; i++)
	{
		chari[i] = '\0';
	}

	for (int i = 1001; i <= 9200; i++)
	{
		sprintf_s(chari, "%4i", i);
		list.Insert(chari);
		cout << "Tree Height is now " << list.GetHeight() << endl;
		//list.PrintList();
		//cin.get();
	}
}