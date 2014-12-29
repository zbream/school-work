public class DivBy5or6
{
	/* Zack Ream
	 * Ex4.11 - Divide by 5 or 6, but not both.
	 * 
	 * This program displays numbers from 100 to 200 that are divisible by 5 or
	 * 6, but not both. It displays these numbers 10 per line, separated by
	 * single spaces. */

	public static void main(String[] args)
	{
		// initialize variables
		int num = 100, lineCounter = 0;
		while (num <= 200)
		{
			// test if divisible by 5 or 6, print number, increase count per
			// line
			if ((num % 5 == 0) ^ (num % 6 == 0))
			{
				System.out.print(num + " ");
				lineCounter++;
				// start new line after 10 values
				if (lineCounter == 10)
				{
					System.out.println();
					lineCounter = 0;
				}
			}

			num++;
		}
	}
}
