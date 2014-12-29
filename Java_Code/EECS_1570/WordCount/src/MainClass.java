import java.io.FileNotFoundException;

import lists.ListType1;
import lists.ListType2;
import lists.ListType3;
import lists.ListType4;
import lists.ListTypeBinary;
import util.ListTester;

/*
 * Tests several implementations of dictionary lists.
 * 
 * Each test is done in its own ListTester.
 * This ListTester will create its own WordReader from the 'filename' argument.
 * Once the ListTester's constructor performs the test, it prints out the test stats.
 * 
 */
public class MainClass
{

	/* Main entry point of the program. */
	public static void main(String[] args) throws FileNotFoundException
	{
		// filename of text file to read from
		final String filename;

		// filename = "wordfile\\Hamlet.txt";
		filename = "wordfile\\Shakespeare.txt";
		
		// LISTTYPE 1
		System.out.println("Test 1: Unsorted List");
		ListTester test1 = new ListTester(new ListType1(), filename);
		test1.printMetrics();
		// test1.writeList("out1.txt");
		System.out.println();

		// LISTTYPE 2
		System.out.println("Test 2: Sorted List");
		ListTester test2 = new ListTester(new ListType2(), filename);
		test2.printMetrics();
		// test2.writeList("out2.txt");
		System.out.println();

		// LISTTYPE 3
		System.out.println("Test 3: Move Match to First");
		ListTester test3 = new ListTester(new ListType3(), filename);
		test3.printMetrics();
		// test3.writeList("out3.txt");
		System.out.println();

		// LISTTYPE 4
		System.out.println("Test 4: Move Match Up One");
		ListTester test4 = new ListTester(new ListType4(), filename);
		test4.printMetrics();
		// test4.writeList("out4.txt");
		System.out.println();
		
		// LISTTYPE 5: BINARY TREE
		System.out.println("Test 5: Binary Tree Dictionary");
		ListTester test5 = new ListTester(new ListTypeBinary(), filename);
		test5.printMetrics();
		// test5.writeList("out5.txt");
		System.out.println();

		System.out.println("Program Finished");
	}

}
