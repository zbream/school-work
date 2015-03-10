/* Ream, Zack - Lab 2 Huffman Trees
EECS 2510 - 03/10/2015 */

#include <string>

// number of characters in the ASCII space
const int CHAR_COUNT = 256;

/*
Represents a single node of a Huffman tree.
*/
struct Node
{
	unsigned char symbol;
	int weight;
	Node *left = NULL;
	Node *right = NULL;

	// Initialize a new leaf node.
	Node(char symbol, int weight) : symbol(symbol), weight(weight) {}

	// Initialize a new internal node.
	Node(int weight) : symbol(NULL), weight(weight) {}
};

/*
Represents the functionality of a Huffman tree.
*/
class Huffman
{
public:
	Huffman();

	/*
	Create the Huffman tree and encoding strings using the given file's character frequencies.
	*/
	void InitializeFromFile(std::string);

	/*
	Huffman encode the given input file to the given output file.
	InitializeFromFile should have been called first.
	*/
	void EncodeFile(std::string in, std::string out);

	/*
	Huffman decode the given input file to the given output file.
	InitializeFromFile should have been called first.
	*/
	void DecodeFile(std::string in, std::string out);

private:
	bool isInitialized = false;

	// Huffman tree
	Node* root = NULL;

	// Huffman character encoding strings
	std::string charStrings[CHAR_COUNT];

	/*
	Recursively populate the charStrings table using the given node.
	Provide an empty starting string when beginning at root.
	*/
	void GeneratePathStrings(Node*, std::string&);
};

