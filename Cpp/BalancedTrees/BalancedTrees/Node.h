#include <string>

struct Node
{
	Node(std::string k) : key(k), count(1) {}

	std::string key;
	int count;

	virtual Node* GetLeft() = 0;
	virtual Node* GetRight() = 0;

	std::string Format()
	{
		return key + " " + std::to_string(count);
	}
};

