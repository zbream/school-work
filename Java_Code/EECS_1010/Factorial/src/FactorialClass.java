import java.util.Scanner;

public class FactorialClass
{
	/* Zack Ream
	 * Factorial
	 * 
	 * This is a program to calculate teh factorial of some number N.
	 * It returns the factorial in the variable F, printed on the console. */
	
	public static void main(String[] args)
	{
		long F = 1; // holds the running product

		// Prompt the user for the integer N
		System.out.println("Enter your desired value of N:");

		// Accept input using the 'Scanner' object
		Scanner input = new Scanner(System.in);
		// N holds the input, the number to find the factorial of
		int N = input.nextInt();
		input.close();

		// loop M from 1 to N
		for (int M = 1; M <= N; M++)
		{
			F *= M;
		}
		// Print F output
		System.out.println("Factorial of " + N + ": " + F);
	}

}
