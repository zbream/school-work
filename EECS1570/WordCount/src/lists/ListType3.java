package lists;

/*
 * A dictionary list that stores words in a self-adjusting list.
 * New/updated entries are moved to the beginning of the list.
 */
public class ListType3 extends AListTypeLinear
{

	/* Adds a word to the list.
	 * If the word is found, increment its count and move it to the beginning.
	 * If not found, add the new node at the beginning of the list. */
	@Override
	public void add(String word)
	{
		// start from beginning of list
		Node prevLoc = null;
		Node loc = first;
		// loop through list, checking for the word
		while (loc != null)
		{
			// a comparison is made, increment count
			comparisonsMade++;
			// if word is found, increase count and move to first
			if (loc.getWord().equals(word))
			{
				// increase count
				loc.incCount();
				// check if start of list
				if (prevLoc == null)
				{
					// word matches with already first word of list, just increment
					return;
				}
				// remove this node from list
				prevLoc.setLink(loc.getLink());
				// reference change made, increment count
				referenceChangesMade++;
				// set this node as first
				setFirst(loc);
				return;
			}
			// word not found, check next
			prevLoc = loc;
			loc = loc.getLink();
		}
		// word not found in list, make it a new node and set first
		setFirst(new Node(word));
	}
}
