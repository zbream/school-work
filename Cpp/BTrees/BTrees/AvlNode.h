#include <string>

struct AvlNode
{
	// record on drive
	int id;

	// payload
	std::string key;
	long count;

	int left;
	int right;

	int BF;
};