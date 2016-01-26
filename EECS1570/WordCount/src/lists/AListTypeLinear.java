package lists;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

/*
 * Provides general functionality across all types of lists with a linked list.
 */
public abstract class AListTypeLinear extends AListType
{
	// first item in the linked-list
	protected Node first;

	// set newNode as first of the list, changing references as necessary
	// this method is used repeatedly through the different types of lists
	protected void setFirst(Node newNode)
	{
		newNode.setLink(first);
		first = newNode;
		// two reference changes made, increase by two
		referenceChangesMade += 2;
	}

	// returns total word count of the list
	@Override
	public int getWordCount()
	{
		int sum = 0;
		// start from beginning of list
		Node test = first;
		// loop through list, adding word count of each node
		while (test != null)
		{
			sum += test.getCount();
			test = test.getLink();
		}
		return sum;
	}

	// returns distinct word count of the list
	@Override
	public int getDistinctWordCount()
	{
		int sum = 0;
		// start from beginning of list
		Node test = first;
		// loop thorugh list, counting each individual word
		while (test != null)
		{
			sum++;
			test = test.getLink();
		}
		return sum;
	}

	// FOR DEBUGGING: print the list to Output
	@Override
	public void printList()
	{
		// start from beginning of list
		Node read = first;
		// loop through list, print each "word, count" to output
		while (read != null)
		{
			System.out.println(read.getWord() + ", " + read.getCount());
			read = read.getLink();
		}
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
			Node read = first;
			// loop through list, write each "word, count" to file
			while (read != null)
			{
				output.println(read.getWord() + ", " + read.getCount());
				read = read.getLink();
			}
			// close the output
			output.close();
		} catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
	}
}
