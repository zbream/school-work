import java.util.Scanner;

public class MergeSortedLists
{
	/* Zack Ream
	 * Ex6.31 - Merge Two Sorted Lists
	 * 
	 * This program accepts input of two lists, each which must be sorted from
	 * least to greatest. The first value of the list indicates how many values
	 * are in the list. The program calls method 'merge', which combines the two
	 * lists, with its elements in order from least to greatest. It does this by
	 * comparing the lowest values of each individually, rather than just
	 * copying the lists and sorting them afterward. */

	public static void main(String[] args)
	{
		// initialize variables
		int[] list1, list2, mergedList;
		int total1, total2;

		// initialize scanner
		Scanner input = new Scanner(System.in);

		// prompt for input of list1
		// read first number entered into total1, the total number of elements
		// initialize list 1, using length entered
		// set list1 to remaining entered values
		System.out.print("Enter list1: ");
		total1 = input.nextInt();
		list1 = new int[total1];
		for (int i = 0; i < total1; i++)
		{
			list1[i] = input.nextInt();
		}

		// prompt for input of list2
		// read first number entered into total2, the total number of elements
		// initialize list 2, using length entered
		// set list1 to remaining entered values
		System.out.print("Enter list2: ");
		total2 = input.nextInt();
		list2 = new int[total2];
		for (int i = 0; i < total2; i++)
		{
			list2[i] = input.nextInt();
		}

		// merge the lists, by calling merge function
		mergedList = merge(list1, list2);

		// output the merged array, by going through and printing each element
		System.out.println("The sorted, merged array is:");
		for (int n : mergedList)
		{
			System.out.print(n + " ");
		}

		input.close();

	}

	public static int[] merge(int[] list1, int[] list2)
	{
		// Accept input of two lists, merge them into mergedReturn, sorted.
		// Return the array.

		// initialize variables
		// totalItems is the number of values of the mergedReturn array, formed
		// from the lengths of the two arrays
		int totalItems = list1.length + list2.length;
		// mergedReturn holds the final array returned by the method
		int[] mergedReturn = new int[totalItems];

		// keeping in mind the loops are in order,
		// each pass of the loop compares the smallest values of each (indexed
		// by x and y), finding the lowest of the two
		// the lowest is placed in the next index (z) of the mergedReturn array
		int x = 0, y = 0, z = 0;
		while (x < list1.length && y < list2.length)
		{
			if (list1[x] <= list2[y])
			{
				mergedReturn[z] = list1[x];
				x++;
				z++;
				continue;
			}
			if (list1[x] > list2[y])
			{
				mergedReturn[z] = list2[y];
				y++;
				z++;
				continue;
			}
		}
		// either list1 or list2 has extra values, which are in order and are
		// the last values of the merged array
		// copy list1 values to end of the array if there are remaining values
		if (x < list1.length)
		{
			java.lang.System.arraycopy(list1, x, mergedReturn, z, list1.length - x);
		}
		// copy list2 values to end of the array if there are remaining values
		if (y < list2.length)
		{
			java.lang.System.arraycopy(list2, y, mergedReturn, z, list2.length - y);
		}

		return mergedReturn;
	}

}
