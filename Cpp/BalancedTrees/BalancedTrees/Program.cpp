#include <iostream>
#include "BstList.h"

using namespace std;

int main()
{
	BstList list = BstList();
	list.Insert("test1");
	list.Insert("test0");
	list.Insert("test0");

	cout << list.GetHeight() << endl;
	cout << list.GetWordCount() << endl;
	cout << list.GetDistinctWordCount() << endl;

	list.PrintList();

	cin.get();
}