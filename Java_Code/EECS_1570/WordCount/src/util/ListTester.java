package util;

import java.io.FileNotFoundException;

import lists.AListType;

/*
 * Class to test one of the ListType derivatives with the file passed to constructor in "filename"
 */
public class ListTester
{
	// declare list to perform test of
	private AListType testList;
	// declare a new WordReader to read words from file
	private WordReader r;

	// time metrics
	private long startTime, endTime;

	/* Constructor for ListTester, accepts an AListType subclass to test, and a filename to read from.
	 * Performs the test. */
	public ListTester(AListType listToTest, String filename) throws FileNotFoundException
	{
		// record beginning time of test (nanoseconds)
		startTime = System.nanoTime();
		// get list type to test
		this.testList = listToTest;
		// create a new WordReader from passed filename
		r = new WordReader(filename);

		// variable to hold a word read from the WordReader
		String word;
		// get a new word, until the function returns null -> EndOfFile
		while ((word = r.getNextWord()) != null)
		{
			// add the read word to the list type we are testing
			testList.add(word);
		}
		
		// close the word file
		r.closeFile();
		
		// record end time of test in relation to startTime (nanoseconds)
		endTime = System.nanoTime();
	}

	// return the amount of time (in nanoseconds) the test took to perform
	public long getTimeTaken()
	{
		return endTime - startTime;
	}

	// print the metrics of the test to the output
	public void printMetrics()
	{
		System.out.println(" Words in the Document: " + testList.getWordCount() + " words.");
		System.out.println(" Distinct Words in the Document: " + testList.getDistinctWordCount() + " words.");
		System.out.println(" Time taken: " + getTimeTaken() + " nanoseconds (" + String.format("%.6f", (getTimeTaken() * Math.pow(10, -9))) + " seconds).");
		System.out.println(" Comparisons made: " + testList.getComparisonCount() + " comparisons.");
		System.out.println(" Reference Changes made: " + testList.getReferenceChangesCount() + " reference changes.");
	}
	
	// FOR DEBUGGING: print the list to Output
	public void printList()
	{
		testList.printList();
	}

	// FOR DEBUGGING: write the list to filename
	public void writeList(String filename)
	{
		testList.writeList(filename);
	}

}
