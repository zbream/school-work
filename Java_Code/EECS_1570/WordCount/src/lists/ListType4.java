package lists;

/*
 * A dictionary list that stores words in a self-adjusting list.
 * Updated entries are moved towards the first node by one node.
 * New entries are added at the beginning of the list.
 */
public class ListType4 extends AListTypeLinear
{
	/* Adds a word to the list.
	 * If the word is found, increment its count and move it up a node.
	 * If not found, add the new node at the beginning of the list. */
	@Override
	public void add(String word)
	{
		// start from beginning of list
		Node loc = first;
		// maintain two previous nodes
		Node parent = null, grandparent = null;

		// loop through list, checking for the word
		while (loc != null)
		{
			// a comparison is made, increment the count
			comparisonsMade++;
			if (loc.getWord().equals(word))
			{
				// word is already in the list, increase its count
				loc.incCount();

				/* word is first in list, no moving required
				 * a| loc MATCH
				 * b|
				 * c|
				 * d| */
				if (parent == null)
				{
					return;
				}

				// always happens regardless of word position in list
				parent.setLink(loc.getLink());
				loc.setLink(parent);

				// two changes made previously, one more must be made in the next if-then
				referenceChangesMade += 3;

				/* word is second in list, it now becomes first
				 * a| parent
				 * b| loc MATCH
				 * c|
				 * d| */
				if (grandparent == null)
				{
					first = loc;
				}

				/* word is third+ in list, move it up one level
				 * a| grandparent
				 * b| parent
				 * c| loc MATCH
				 * d| */
				else
				{
					grandparent.setLink(loc);
				}

				return;
			}
			// word not found, check next
			grandparent = parent;
			parent = loc;
			loc = loc.getLink();
		}
		// word not found in list, make it a new node and set first
		setFirst(new Node(word));
	}

}
