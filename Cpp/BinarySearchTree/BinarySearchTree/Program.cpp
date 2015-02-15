/* Ream, Zack - Lab 1 BST
EECS 2510 - 02/17/2015 */

#include <iostream>
#include <string>
#include "Bst.h"

using namespace std;

// function declarations
bool strEquals(const string&, const string&);

// main entry point of the application
int main()
{
	// create an empty tree
	Bst* tree = new Bst();

	// begin looping for commands
	string input, parameter;
	while (true)
	{
		// get command
		cin >> input;

		if (strEquals(input, "search"))
		{
			cin >> parameter;

			tree->Search(parameter);
		}
		else if (strEquals(input, "insert"))
		{
			cin >> parameter;

			tree->Insert(parameter);
		}
		else if (strEquals(input, "delete"))
		{
			cin >> parameter;

			tree->Delete(parameter);
		}
		else if (strEquals(input, "min"))
		{
			tree->Min();
		}
		else if (strEquals(input, "max"))
		{
			tree->Max();
		}
		else if (strEquals(input, "next"))
		{
			cin >> parameter;

			tree->Next(parameter);
		}
		else if (strEquals(input, "prev"))
		{
			cin >> parameter;

			tree->Prev(parameter);
		}
		else if (strEquals(input, "list"))
		{
			tree->List();
		}
		else if (strEquals(input, "help"))
		{
			cout
				<< "insert <s> - add <s>\n"
				<< "delete <s> - remove <s>\n"
				<< "search <s> - return <s>\n"
				<< "min        - minimum value in list\n"
				<< "max        - maximum value in list\n"
				<< "next <s>   - successor to <s> in list\n"
				<< "prev <s>   - predecessor to <s> in list\n"
				<< "list       - list words in ascending order\n"
				<< "help       - view this list of commands\n"
				<< "exit       - terminate the program\n";
		}
		else if (strEquals(input, "exit"))
		{
			return 0;
		}
		else
		{
			cout << "Not a command." << endl;
		}
	}
}

/*
Performs a case-insensitive comparison of the specified string against the specified reference string.

ASSUME: the reference string is all lowercase
*/
bool strEquals(const string& const s, const string& const reference)
{
	int length = reference.length();

	// check if strings are equal length
	if (s.length() != length)
	{
		return false;
	}

	// check if each char matches (case-insensitive)
	for (int i = 0; i < length; i++)
	{
		if (tolower(s[i]) != reference[i])
		{
			return false;
		}
	}

	return true;
}