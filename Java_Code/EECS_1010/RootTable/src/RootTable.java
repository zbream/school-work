public class RootTable
{
	/* Zack Ream
	 * RootTable
	 * 
	 * This program outputs a table of square roots of all integers from 0 to
	 * 100 to demonstrate the use fo nested for-loops. */

	public static void main(String[] args)
	{
		System.out.println("   |  0    1    2    3    4    5    6    7    8    9");
		System.out.println("---+--------------------------------------------------");
		for (int row = 0; row <= 90; row += 10)
		{
			System.out.printf("%2d | ", row);
			for (int col = 0; col <= 9; col++)
			{
				System.out.printf("%4.2f ", Math.sqrt(row + col));
			}
			System.out.println();
		}

	}

}
