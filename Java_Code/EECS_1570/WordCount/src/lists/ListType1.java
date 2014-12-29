package lists;

/*
 * A dictionary list that stores words in an unsorted link list.
 * New entries are added to the beginning of the list.
 */
public class ListType1 extends AListTypeLinear
{

	/* Adds a word to the list.
	 * If the word is found, just increment its count.
	 * If not found, add a new node at the beginning of the list. */
	@Override
	public void add(String word)
	{
		// start from beginning of list
		Node loc = first;
		// loop through list, checking for the word
		while (loc != null)
		{
			// a comparison is made, increment count
			comparisonsMade++;
			if (loc.getWord().equals(word))
			{
				// the word is found, increase its count
				loc.incCount();
				return;
			}
			// the word is not found in that node, get next, loop
			loc = loc.getLink();
		}
		// word is not found in the list, add it to beginning in new node
		setFirst(new Node(word));
	}

}
