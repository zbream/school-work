/* Ream, Zack - Lab3 Balanced Trees
EECS 2510 - 4/7/2015

Program.cpp
Compares the Binary Search Tree (BstList), AVL tree (AvlList), and Red-Black tree (RbList) with the same data from a file.
Provides metrics including real time taken, operations taken, total words found, etc. */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
#include "BstList.h"
#include "AvlList.h"
#include "RbList.h"

using namespace std;

// max width of an output string (see Disp())
const int DISP_WIDTH = 19;

// max width of an input word (See ReadText())
const int MAX_INPUT_WIDTH = 200;

// prototypes
void Disp(string message, long value);
long ReadText(string&, WordList&);
long ReadText(string&);
void TestNumbers(WordList&);

// Main entry point of the program.
int main()
{
	string src = "Shakespeare.txt";
	//string src = "Hamlet.txt";
	//string src = "Dictionary.txt";

	// dry run
	cout << "Dry run...\n";
	long dryTime = ReadText(src);
	Disp("RunTime (ms)", dryTime);

	// BST
	cout << "\nBST...\n";
	BstList bstList = BstList();
	long bstTime = ReadText(src, bstList);
	Disp("RunTime (ms)", bstTime);
	Disp("Total Word Count", bstList.GetWordCount());
	Disp("Distinct Word Count", bstList.GetDistinctWordCount());
	Disp("Tree Height", bstList.GetHeight());
	Disp("Comparisons Made", bstList.GetComparisonsMade());
	Disp("Pointers Changed", bstList.GetPointerChangesMade());

	// AVL
	cout << "\nAVL...\n";
	AvlList avlList = AvlList();
	long avlTime = ReadText(src, avlList);
	Disp("RunTime (ms)", avlTime);
	Disp("Total Word Count", avlList.GetWordCount());
	Disp("Distinct Word Count", avlList.GetDistinctWordCount());
	Disp("Tree Height", avlList.GetHeight());
	Disp("Comparisons Made", avlList.GetComparisonsMade());
	Disp("Pointers Changed", avlList.GetPointerChangesMade());
	Disp("BF Adjustments", avlList.GetBFChangesMade());

	// RB
	cout << "\nRB...\n";
	RbList rbList = RbList();
	long rbTime = ReadText(src, rbList);
	Disp("RunTime (ms)", rbTime);
	Disp("Total Word Count", rbList.GetWordCount());
	Disp("Distinct Word Count", rbList.GetDistinctWordCount());
	Disp("Tree Height", rbList.GetHeight());
	Disp("Comparisons Made", rbList.GetComparisonsMade());
	Disp("Pointers Changed", rbList.GetPointerChangesMade());
	Disp("Recolorings", rbList.GetRecoloringsMade());
	
	// finished
	cout << "\ndone";
	cin.get();
}

/*
Display a formatted metric, using the given message and value.
Makes the output easier to follow.
*/
void Disp(string message, long value)
{
	cout << setw(DISP_WIDTH) << message << ": " << value << endl;
}

/*
Read words from the given file, Adds into the given WordList.
Returns the time (in ms) taken.
*/
long ReadText(string& file, WordList& wordList)
{
	char c;
	char chari[MAX_INPUT_WIDTH];
	int iPtr;
	bool isDelimiter = false, wasDelimiter = false;
	for (int i = 0; i < MAX_INPUT_WIDTH; i++) chari[i] = '\0';

	// open stream
	ifstream inFile(file, ios::binary);
	if (inFile.fail())
	{
		cout << "Unable to read input file.\n";
		cin.get();
		exit(1);
	}

	// start time
	clock_t timeBegin = clock();

	iPtr = 0;
	inFile.get(c);
	while (!inFile.eof())
	{
		isDelimiter = (c == 32 || c == 10 || c == 13 || c == 9 ||
			c == '.' || c == ',' || c == '!' || c == ';' ||
			c == ':' || c == '(' || c == ')');
		
		if (isDelimiter && !wasDelimiter)
		{
			wasDelimiter = true;
			wordList.Insert(chari);

			for (int i = 0; i < MAX_INPUT_WIDTH; i++) chari[i] = '\0';
			iPtr = 0;
		}
		else if (!isDelimiter)
		{
			chari[iPtr++] = c;
		}
		else if (isDelimiter && wasDelimiter)
		{
			// do nothing
		}

		// prepare for next iteration
		wasDelimiter = isDelimiter;
		inFile.get(c);
	}

	// end time
	clock_t timeEnd = clock();

	inFile.close();

	return timeEnd - timeBegin;
}

/*
Read words from the given file, as a dry run.
Returns the time (in ms) taken.
*/
long ReadText(string& file)
{
	char c;
	char chari[MAX_INPUT_WIDTH];
	int iPtr;
	bool isDelimiter = false, wasDelimiter = false;
	for (int i = 0; i < MAX_INPUT_WIDTH; i++) chari[i] = '\0';

	// open stream
	ifstream inFile(file, ios::binary);
	if (inFile.fail())
	{
		cout << "Unable to read input file.\n";
		cin.get();
		exit(1);
	}

	// start time
	clock_t timeBegin = clock();

	iPtr = 0;
	inFile.get(c);
	while (!inFile.eof())
	{
		isDelimiter = (c == 32 || c == 10 || c == 13 || c == 9 ||
			c == '.' || c == ',' || c == '!' || c == ';' ||
			c == ':' || c == '(' || c == ')');

		if (isDelimiter && !wasDelimiter)
		{
			wasDelimiter = true;
			// NO LIST INSERT

			for (int i = 0; i < MAX_INPUT_WIDTH; i++) chari[i] = '\0';
			iPtr = 0;
		}
		else if (!isDelimiter)
		{
			chari[iPtr++] = c;
		}
		else if (isDelimiter && wasDelimiter)
		{
			// do nothing
		}

		// prepare for next iteration
		wasDelimiter = isDelimiter;
		inFile.get(c);
	}

	// end time
	clock_t timeEnd = clock();

	inFile.close();

	return timeEnd - timeBegin;
}

/*
Test the given list with 8200 values added in-order.
*/
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
		//cout << "Tree Height is now " << list.GetHeight() << endl;
		//list.PrintList();
		//cin.get();
	}
}