/* Ream, Zack - Lab4 BTrees
EECS 2510 - 4/25/2015

Program.cpp
This program compares the efficiency of disk-based search trees.
Trees considered include the AVL-tree and the B-tree. */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
#include "AvlList.h"
#include "BList.h"

using namespace std;

// max width of an output string (see Disp())
const int DISP_WIDTH = 19;

// max width of an input word (See ReadText())
const int MAX_INPUT_WIDTH = 200;

// prototypes
void StandardTest(WordList&, string&);
void Disp(string message, long value);
long ReadText(string&, WordList&);

// Main entry point of the program.
int main()
{
	//string avlIOFolder = "D:\\Zack\\Desktop\\Files\\AVL\\";
	//string bIOFolder = "D:\\Zack\\Desktop\\Files\\B\\";

	string avlIOFile = "D:\\Zack\\Desktop\\Files\\avl.txt";
	string bIOFile = "D:\\Zack\\Desktop\\Files\\b.txt";

	string src = "Hamlet.txt";
	
	// AVL
	cout << "\nAVL...\n";
	AvlList avlList(avlIOFile);
	StandardTest(avlList, src);

	// B
	cout << "\nB...\n";
	BList bList(bIOFile);
	StandardTest(bList, src);

	cin.get();
}

void StandardTest(WordList& list, string& inputfile)
{
	long time = ReadText(inputfile, list);
	Disp("RunTime (ms)", time);
	Disp("Total Word Count", list.GetWordCount());
	Disp("Distinct Word Count", list.GetDistinctWordCount());
	Disp("Tree Height", list.GetHeight());
	Disp("Disk Allocations", list.GetDiskAlloc());
	Disp("Disk Reads", list.GetDiskReads());
	Disp("Disk Writes", list.GetDiskWrites());
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
	for (int i = 0; i < MAX_INPUT_WIDTH; ++i) chari[i] = '\0';

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