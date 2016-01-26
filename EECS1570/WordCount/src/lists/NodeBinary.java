package lists;

/*
 * A single node of a ListType's binary tree. Keeps track of left/right child.
 */
public class NodeBinary
{
	// data variables
	private String word;
	private int count;
	// link to next nodes
	private NodeBinary left, right;

	// Constructor, starts off with a word, and count=1 (since we obviously found the word once)
	public NodeBinary(String word)
	{
		this.word = word;
		this.count = 1;
		this.left = this.right = null;
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

	// return left child
	public NodeBinary getLeft()
	{
		return left;
	}

	// set left child
	public void setLeft(NodeBinary link)
	{
		this.left = link;
	}

	// return right child
	public NodeBinary getRight()
	{
		return right;
	}

	// set right child
	public void setRight(NodeBinary link)
	{
		this.right = link;
	}
}
