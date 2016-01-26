import java.util.Scanner;

public class LuhnClass
{
	/* Zack Ream
	 * Luhn Algorithm
	 * 
	 * This program confirms whether or not a credit card number is valid using
	 * the Luhn algorithm.
	 * Accepts input for a credit card number, returns boolean true/false. */
	
	public static void main(String[] args)
	{
		// Prompt for Credit Card Number
		System.out.println("Enter a credit-card number:");

		// Accept Credit Card Number
		Scanner input = new Scanner(System.in);
		long cCardNumber = input.nextLong();
		input.close();

		long cCardNumber2 = cCardNumber;
		long runningSum = 0;

		/**
		 * The Luhn Algorithm: Counting from the right, double every second
		 * digit. If the result>9, then subtract 9. Add all the numbers. If the
		 * sum is a multiple of 10, the card is valid.
		 */
		// Loop through each digit of the card
		do
		{
			// get the right-most digit of cCardNumber
			long digit1 = cCardNumber % 10;
			// remove the last digit from cCardNumber
			// integer cuts off the fraction portion, removing the last digit
			cCardNumber /= 10;
			// get the NEW right-most digit of cCardNumber
			long digit2 = cCardNumber % 10;
			// again, remove the last digit from cCardNumber
			cCardNumber /= 10;
			// double it
			digit2 *= 2;
			// subtract 9 if the digit is greater than 9
			if (digit2 > 9)
				digit2 -= 9;
			// add the numbers to the runningSum
			runningSum += (digit2 + digit1);
		} while (cCardNumber > 0);
		// Return whether or not the card is valid

		if ((runningSum % 10) == 0)
		{
			// If the sum of the digits ends in zero, then the sum is
			// a multiple of 10, and thus the card number is valid.
			System.out.println("The credit card number " + cCardNumber2 + " is valid.");
		} else
		{
			System.out.println("The credit card number " + cCardNumber2 + " is invalid.");
		}
	}

}
