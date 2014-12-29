package lists;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

/*
 * Provides functionality for a Binary Tree list.
 */
public class ListTypeBinary extends AListType
{
	// root of the tree
	protected NodeBinary root;

	/* Adds a word to the list.
	 * If the word is not found, add a node to its appropriate spot.
	 * If the word is found, just incrememnt its count. */
	@Override
	public void add(String word)
	{
		// x is current node, y lags behind to keep track of the parent node
		NodeBinary y = null, x = root;

		// first phase: look for the node, or where it should be
		while (x != null)
		{
			// move 'x' node to parent reference 'y'
			y = x;

			// int of comparison between added word and word in current node
			int comparison = word.compareTo(x.getWord());
			// a comparison is made, increment the count
			comparisonsMade++;

			/* If the node is a match, increment its count and end method.
			 * If not, move left or right, depending on comparison. */
			if (comparison == 0) // node is a match
			{
				x.incCount();
				return;
			} else
			{
				// a reference must be changed, increment the count
				if (comparison < 0)
				{
					x = x.getLeft();
				} else
				{
					x = x.getRight();
				}
			}
		}
		// at this point, x==null, y holds the parent of the new node

		// second phase: add the word to the tree in a new ndoe
		NodeBinary newNode = new NodeBinary(word);

		// if parent reference is STILL null, the tree is empty; create root
		if (y == null)
		{
			root = newNode;
		} else
		{
			// a comparison is made, and a reference must be changed; increment
			comparisonsMade++;
			referenceChangesMade++;
			// put new node to left/right child of the 'y' node
			if (word.compareTo(y.getWord()) < 0)
			{
				y.setLeft(newNode);
			} else
			{
				y.setRight(newNode);
			}
		}
	}

	// returns total word count of the list
	@Override
	public int getWordCount()
	{
		return countWords(root);
	}

	// recursively finds total words in a tree, given its root
	private int countWords(NodeBinary node)
	{
		// node is null, no words in its "tree"
		if (node == null)
		{
			return 0;
		}
		// return sum of this node, and its children's tree
		return (node.getCount() + countWords(node.getLeft()) + countWords(node.getRight()));

	}

	// returns distinct word count of the list
	@Override
	public int getDistinctWordCount()
	{
		return countDistinctWords(root);
	}

	// recursively finds distinct words in a tree, given its root
	private int countDistinctWords(NodeBinary node)
	{
		// node is null, no words in its "tree"
		if (node == null)
		{
			return 0;
		}
		// return sum of this node, and its children's tree
		return (1 + countDistinctWords(node.getLeft()) + countDistinctWords(node.getRight()));
	}

	// FOR DEBUGGING: print the list to Output
	@Override
	public void printList()
	{
		printNode(root);
	}

	// recursively prints a tree to output, given its root
	private void printNode(NodeBinary node)
	{
		// node is null, no words in its "tree"
		if (node == null)
		{
			return;
		}
		// print in order L, root, R
		printNode(node.getLeft());
		System.out.println(node.getWord() + ", " + node.getCount());
		printNode(node.getRight());
	}

	// FOR DEBUGGING: write the list to filename
	@Override
	public void writeList(String filename)
	{
		// catch error of invalid file
		try
		{
			PrintWriter output = new PrintWriter(new File(filename));

			// start from beginning of list
			writeNode(root, output);

			// close the output
			output.close();
		} catch (FileNotFoundException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	// recursively writes a tree to filename, given its root
	private void writeNode(NodeBinary node, PrintWriter output)
	{
		// node is null, no words in its "tree"
		if (node == null)
		{
			return;
		}
		// write in order L, root, R
		writeNode(node.getLeft(), output);
		output.println(node.getWord() + ", " + node.getCount());
		writeNode(node.getRight(), output);
	}

}
