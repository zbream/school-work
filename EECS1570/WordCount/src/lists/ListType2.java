package lists;

/*
 * A dictionary list that stores words in a sorted link list.
 * New entries are added in their alphabetical position.
 * 
 * Loop through the list until the added word is or comes before a node.
 *  In other words, loop while the added word comes after a node.
 * If the node found equals the added word, then increment the count.
 * If not, then insert the new word before this found node.
 * 
 * EXAMPLE: ADD c
 * a	loc			-a comes before c (comparisonResult == -1)
 * b		loc		-b comes before c (cR == -1)
 * d			loc	-d comes after c (cR == 1), keep this loc, move on
 */
public class ListType2 extends AListTypeLinear
{
	/* Adds a word to the list.
	 * If the word is found, just increment its count.
	 * If not found, add a new node in its proper alphabetical position. */
	@Override
	public void add(String word)
	{
		// start from beginning of list
		Node prevLoc = null;
		Node loc = first;
		// assume word comes before loc, incase list is empty (while loop is skipped)
		int comparisonResult = 1;
		// loop through list, looking for the word
		while (loc != null)
		{
			/* Compare current node to added word
			 * 0: the words are the same
			 * -1: loc, word
			 * 1: word, loc */
			comparisonResult = loc.getWord().compareTo(word);
			// a comparison was made, increment count
			comparisonsMade++;
			// if loc comes after word, or loc is word, stop the loop, keep loc
			if (comparisonResult >= 0)
			{
				break;
			}
			// if not, move to the next node
			prevLoc = loc;
			loc = loc.getLink();
		}
		// if loc matches the word, increment its count
		if (comparisonResult == 0)
		{
			loc.incCount();
		} else // otherwise, add the new node at loc's position
		{
			// create the new node
			Node newNode = new Node(word);
			// if loc is the start of the list, create a new first node
			if (prevLoc == null)
			{
				newNode.setLink(first);
				first = newNode;
				referenceChangesMade += 2;
			} else //otherwise, insert the new node
			{
				prevLoc.setLink(newNode);
				newNode.setLink(loc);
				referenceChangesMade += 2;
			}
		}
	}
}
