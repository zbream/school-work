package lists;

/*
 * Provides general functionality across all types of lists.
 */
public abstract class AListType
{
	// Abstract method for All Types: Adds a word to the list.
	public abstract void add(String word);

	// keep track of metrics
	protected long comparisonsMade = 0, referenceChangesMade = 0;

	// returns total word count of the list
	public abstract int getWordCount();

	// returns distinct word count of the list
	public abstract int getDistinctWordCount();

	// return comparisons made in the test
	public long getComparisonCount()
	{
		return comparisonsMade;
	}

	// return references changes made in the test
	public long getReferenceChangesCount()
	{
		return referenceChangesMade;
	}

	// FOR DEBUGGING: print the list to Output
	public abstract void printList();

	// FOR DEBUGGING: write the list to filename
	public abstract void writeList(String filename);
}
