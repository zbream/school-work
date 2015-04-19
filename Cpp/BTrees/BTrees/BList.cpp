#include <iostream>
#include "BList.h"

using namespace std;

BList::BList() : io("D:\\Zack\\Desktop\\Files\\")
{
	BNode x;
	io.AllocateNode(x);
	x.isLeaf = true;
	x.n = 0;

	io.WriteNode(x, x.id);
	root = x.id;
}

void BList::Insert(string k)
{
	// get the node
	BNode r;
	io.ReadNode(root, r);

	// increment a key's count, if the key exists
	if (addIfExists(r, k))
	{
		return;
	}
	// otherwise, insert the new key

	// check if the root node is full
	if (r.n == (2 * r.T - 1))
	{
		// root is full, split it
		BNode s;
		io.AllocateNode(s);

		root = s.id;
		s.isLeaf = false;
		s.n = 0;
		s.children[0] = r.id;

		splitChild(s, 0, r);
		insertNonFull(s, k);
	}
	else
	{
		insertNonFull(r, k);
	}
}

bool BList::addIfExists(BNode x, std::string& k)
{
	while (true)
	{
		int i = 0;

		while (i < x.n && k > x.keys[i].key)
		{
			++i;
		}

		if (i < x.n && k == x.keys[i].key)
		{
			++(x.keys[i].count);
			io.WriteNode(x, x.id);
			return true;
		}

		if (x.isLeaf)
		{
			return false;
		}

		io.ReadNode(x.children[i], x);

	}


}



void BList::insertNonFull(BNode& x, std::string& k)
{
	int i = x.n - 1;
	if (x.isLeaf)
	{
		while (i >= 0 && k < x.keys[i].key)
		{
			x.keys[i + 1] = x.keys[i];
			--i;
		}
		x.keys[i + 1].key = k;
		x.keys[i + 1].count = 1;
		++(x.n);
		io.WriteNode(x, x.id);
	}
	else
	{
		while (i >= 0 && k < x.keys[i].key)
		{
			--i;
		}

		//if (i >= 0 && k == x.keys[i].key)
		//{
		//	// found the key already
		//	++(x.keys[i].count);
		//	io.WriteNode(x, x.id);
		//	return;
		//}

		++i;

		BNode xi;
		io.ReadNode(x.children[i], xi);

		if (xi.n == (2 * xi.T - 1))
		{
			splitChild(x, i, xi);
			if (k > x.keys[i].key)
			{
				io.ReadNode(x.children[i + 1], xi);
			}
		}

		insertNonFull(xi, k);
	}
}

void BList::splitChild(BNode& x, int i, BNode& y)
{
	BNode z;
	io.AllocateNode(z);

	z.isLeaf = y.isLeaf;
	z.n = z.T - 1;

	for (int j = 0; j < z.T - 1; j++)
	{
		z.keys[j] = y.keys[j + z.T];
	}

	if (!y.isLeaf)
	{
		for (int j = 0; j < z.T; j++)
		{
			z.children[j] = y.children[j + z.T];
		}
	}

	y.n = z.T - 1;

	// make z a child of x
	for (int j = x.n; j > i; j--)
	{
		x.children[j + 1] = x.children[j];
	}

	x.children[i + 1] = z.id;

	for (int j = x.n - 1; j >= i; j--)
	{
		x.keys[j + 1] = x.keys[j];
	}

	x.keys[i] = y.keys[z.T - 1];
	++(x.n);

	io.WriteNode(y, y.id);
	io.WriteNode(z, z.id);
	io.WriteNode(x, x.id);
}

int BList::getLevelCount(int id)
{
	BNode node;
	io.ReadNode(id, node);

	if (node.isLeaf)
	{
		return 1;
	}
	else
	{
		return(1 + getLevelCount(node.children[0]));
	}
}

int BList::getWordCount(int id)
{
	BNode node;
	io.ReadNode(id, node);

	int count = 0;
	for (int j = 0; j < node.n; ++j)
	{
		count += node.keys[j].count;
	}

	// continue down if there are children
	if (!node.isLeaf)
	{
		for (int j = 0; j <= node.n; ++j)
		{
			count += getWordCount(node.children[j]);
		}
	}

	return count;
}

int BList::getDistinctWordCount(int id)
{
	BNode node;
	io.ReadNode(id, node);

	int count = node.n;

	if (!node.isLeaf)
	{
		for (int j = 0; j <= node.n; ++j)
		{
			count += getDistinctWordCount(node.children[j]);
		}
	}

	return count;
}

void BList::printNode(int id)
{

}