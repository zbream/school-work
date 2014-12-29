package lists;

/*
 * A single node of a ListType's linearly-linked list. Keeps track of next node.
 */
public class Node
{
	// data variables
	private String word;
	private int count;
	// link to next node
	private Node link;

	// Constructor, starts off with a word, and count=1 (since we obviously found the word once)
	public Node(String word)
	{
		this.word = word;
		this.count = 1;
		this.link = null;
	}

	// return word
	public String getWord()
	{
		return word;
	}

	// return count for the word
	public int getCount()
	{
		return count;
	}

	// increase the count by 1 (word found)
	public void incCount()
	{
		this.count++;
	}

	// return next node in list
	public Node getLink()
	{
		return link;
	}

	// set next node in list
	public void setLink(Node link)
	{
		this.link = link;
	}
}