/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include <iostream>
#include <limits>
#include <time.h>
#include "Huffman.h"
#include "OutBuffer.h"
#include "InBuffer.h"

using namespace std;

Huffman::Huffman()
{
}

void Huffman::InitializeFromFile(string fileName)
{
	// == populate frequency table
	int charFrequencies[CHAR_COUNT] = {};

	// open stream
	ifstream inputStream(fileName, ios::binary);
	if (inputStream.fail())
	{
		cout << "Unable to read input file.\n";
		exit(1);
	}

	// metrics
	int bytesIn = 0;
	clock_t timeBegin = clock();

	// read char by char
	int charRead = inputStream.get();
	while (!inputStream.eof())
	{
		charFrequencies[charRead]++;
		++bytesIn;

		charRead = inputStream.get();
	}

	inputStream.close();

	// == create huffman tree
	Node* nodes[CHAR_COUNT];

	// initialize nodes
	for (int i = 0; i < CHAR_COUNT; i++)
	{
		nodes[i] = new Node((unsigned char)i, charFrequencies[i]);
	}

	// make just enough passes to be left with 1 node in the array
	for (int pass = 1; pass < CHAR_COUNT; pass++)
	{
		// get the index of the two smallest weights
		int min1Index = 0, min2Index = 0;
		int min1Weight = INT_MAX, min2Weight = INT_MAX;

		// get the smallest
		for (int i = 0; i < CHAR_COUNT; i++)
		{
			if (nodes[i] != NULL)
			{
				if (nodes[i]->weight < min1Weight)
				{
					min1Index = i;
					min1Weight = nodes[i]->weight;
				}
			}
		}

		// get the next-smallest
		for (int i = 0; i < CHAR_COUNT; i++)
		{
			if (nodes[i] != NULL && i != min1Index)
			{
				if (nodes[i]->weight < min2Weight)
				{
					min2Index = i;
					min2Weight = nodes[i]->weight;
				}
			}
		}

		// create new internal node, replace first child
		Node* newNode = new Node(nodes[min1Index]->weight + nodes[min2Index]->weight);
		newNode->left = nodes[min1Index];
		newNode->right = nodes[min2Index];
		nodes[min2Index] = NULL;
		nodes[min1Index] = newNode;
	}

	// at this point, one node remains; find it
	for (int i = 0; i < CHAR_COUNT; i++)
	{
		if (nodes[i] != NULL)
		{
			root = nodes[i];
			break;
		}
	}

	GeneratePathStrings(root, string());

	// calculate time
	clock_t timeEnd = clock();
	long time = timeEnd - timeBegin;

	// print metrics
	cout << "Initialization:" << endl
		<< "Time (ms): " << time << endl
		<< "Bytes In:  " << bytesIn << endl;

	isInitialized = true;
}

void Huffman::GeneratePathStrings(Node* node, string& pathToHere)
{
	// first, assume node is a leaf
	// if we find child pointers, node is not a leaf
	bool isLeaf = true;

	if (node->left != NULL)
	{
		GeneratePathStrings(node->left, pathToHere + "0");
		isLeaf = false;
	}

	if (node->right != NULL)
	{
		GeneratePathStrings(node->right, pathToHere + "1");
		isLeaf = false;
	}

	if (isLeaf)
	{
		// node is a leaf, so the current path leads to a char
		charStrings[node->symbol] = pathToHere;
	}
}

void Huffman::EncodeFile(string inFile, string outFile)
{
	// check for initialization
	if (!isInitialized)
	{
		cout << "Call InitializeFromFile() first.";
		exit(1);
	}

	// open input file stream
	ifstream inStream(inFile, ios::binary);
	if (inStream.fail())
	{
		cout << "Unable to read input file.\n";
		exit(1);
	}

	// open output file stream
	ofstream outStream = ofstream(outFile, ios::binary);
	if (outStream.fail())
	{
		cout << "Unable to create output file.\n";
		exit(1);
	}

	// metrics
	int bytesIn = 0, bytesOut;
	clock_t timeBegin = clock();

	// create output buffer around output file
	OutBuffer buffer(outStream);

	// read input file, char-by-char; write to output buffer
	unsigned char charRead = inStream.get();
	while (!inStream.eof())
	{
		buffer.Write(charStrings[charRead]);

		charRead = inStream.get();
		++bytesIn;
	}

	// find suitable padding string
	string* paddingString = NULL;
	unsigned int remainingBits = buffer.GetRemainingBits();
	for (int i = 0; i < CHAR_COUNT; i++)
	{
		// need a path that is longer than the remaining bits we need to fill
		if (charStrings[i].length() > remainingBits)
		{
			paddingString = &charStrings[i];
			break;
		}
	}

	if (paddingString == NULL)
	{
		cout << "No suitable padding-string found.";
		exit(1);
	}

	// write just enough bits to force a flush of the buffer
	buffer.Write(paddingString->substr(0, remainingBits));

	bytesOut = buffer.GetBytesOut();

	// close the streams
	outStream.close();
	inStream.close();

	// calculate time
	clock_t timeEnd = clock();
	long time = timeEnd - timeBegin;

	// print metrics
	double ratio = ((double)bytesOut / bytesIn) * 100.0;

	cout << "Encode:" << endl
		<< "Time (ms): " << time << endl
		<< "Bytes In:  " << bytesIn << endl
		<< "Bytes Out: " << bytesOut << endl << endl
		<< "Compression Ratio: " << ratio << endl;
}

void Huffman::DecodeFile(string inFile, string outFile)
{
	// check for initialization
	if (!isInitialized)
	{
		cout << "Call InitializeFromFile() first.";
		exit(1);
	}

	// open input file stream
	ifstream inStream(inFile, ios::binary);
	if (inStream.fail())
	{
		cout << "Unable to read input file.\n";
		exit(1);
	}

	// open output file stream
	ofstream outStream = ofstream(outFile, ios::binary);
	if (outStream.fail())
	{
		cout << "Unable to create output file.\n";
		exit(1);
	}

	// metrics
	int bytesIn, bytesOut = 0;
	clock_t timeBegin = clock();

	// create input buffer around input file
	InBuffer buffer(inStream);

	Node* current = root;
	int bit = buffer.Read();

	// stop navigating the tree if no more bits
	while (bit != -1)
	{
		// if we are at a leaf, write the char to output stream, restart at root
		if (current->left == NULL && current->right == NULL)
		{
			outStream.put(current->symbol);
			++bytesOut;

			current = root;
		}

		// follow the path of the currently-read bit
		if (bit == 0)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}

		bit = buffer.Read();
	}

	bytesIn = buffer.GetBytesIn();

	// close the streams
	outStream.close();
	inStream.close();

	// calculate time
	clock_t timeEnd = clock();
	long time = timeEnd - timeBegin;

	// print metrics
	cout << "Decode:" << endl
		<< "Time (ms): " << time << endl
		<< "Bytes In:  " << bytesIn << endl
		<< "Bytes Out: " << bytesOut << endl;
}