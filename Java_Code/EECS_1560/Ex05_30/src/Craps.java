public class Craps
{
	/* Zack Ream
	 * Ex5.30 - Craps
	 * 
	 * This program runs a simple round of the dice game Craps. */

	public static void main(String[] args)
	{
		// initialize variables, roll two dice
		int roll = rollDice();

		// lose if sum is 2,3,12
		if (roll == 2 || roll == 3 || roll == 12)
		{
			System.out.println(" You Lose");
		}

		// win if sum is 7,11
		else if (roll == 7 || roll == 11)
		{
			System.out.println(" You Win");
		}

		// start point sequence
		else
		{
			int point = roll;
			System.out.println(" Point is " + point);
			while (true)
			{
				roll = rollDice();
				if (roll == 7)
				{
					System.out.println(" You Lose");
					break;
				} else if (roll == point)
				{
					System.out.println(" You Win");
					break;
				}
			}
		}

	}

	public static int rollDice()
	{
		// This method rolls two 6-sided dice, and returns the sum.

		// initialize variables
		int die1, die2, sum;

		// roll two dice, each 1-6, compute the total
		die1 = (int) (1 + Math.random() * 6);
		die2 = (int) (1 + Math.random() * 6);
		sum = die1 + die2;
		System.out.println("You rolled " + die1 + " + " + die2 + " = " + sum);
		return sum;
	}
}
