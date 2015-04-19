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
void Disp(string message, long value);
long ReadText(string&, WordList&);

// Main entry point of the program.
int main()
{
	string src = "Hamlet.txt";
	
	// AVL
	//cout << "\nAVL...\n";
	//AvlList avlList = AvlList();
	//long avlTime = ReadText(src, avlList);
	//Disp("RunTime (ms)", avlTime);
	//Disp("Total Word Count", avlList.GetWordCount());
	//Disp("Distinct Word Count", avlList.GetDistinctWordCount());
	//Disp("Tree Height", avlList.GetHeight());
	//Disp("Disk Allocations", avlList.GetDiskAlloc());
	//Disp("Disk Reads", avlList.GetDiskReads());
	//Disp("Disk Writes", avlList.GetDiskWrites());

	BList list = BList();

	list.Insert("F");
	list.Insert("S");
	list.Insert("Q");
	list.Insert("K");
	list.Insert("C");
	list.Insert("L");
	list.Insert("H");
	list.Insert("T");
	list.Insert("V");
	list.Insert("W");
	list.Insert("M");
	list.Insert("R");
	list.Insert("N");
	list.Insert("P");
	list.Insert("A");
	list.Insert("B");
	list.Insert("X");
	list.Insert("Y");
	list.Insert("D");
	list.Insert("Z");
	list.Insert("E");
	list.Insert("E");

	cout << list.GetWordCount() << endl;
	cout << list.GetDistinctWordCount();

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