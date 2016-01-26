import java.math.BigInteger;

public class mersenneMain
{
	/* Zack Ream
	 * Ex10.19 - Mersenne Primes
	 * 
	 * This program displays the subset of prime numbers called the Mersenne
	 * Primes. These numbers are prime numbers that can be written in the form
	 * (2^p + 1). This program displays all of them from p=1..100. */

	public static void main(String[] args)
	{
		// display the top of the table (header)
		System.out.println(" p  | 2^p - 1");
		System.out.println("----+--------");

		/* loop through the p-values. Skip p=1, since 1 is neither prime nor
		 * composite */
		for (int p = 2; p <= 100; p++)
		{
			// if p is prime, then it has a Mersenne prime using the function
			if (isPrime(p))
			{
				System.out.printf("%3d | ", p);
				System.out.println(function(p));
			}
		}

	}

	static BigInteger function(int p)
	{
		// use big integer to calculate the Mersenne Prime (since they get huge)
		BigInteger big = new BigInteger("2");
		big = big.pow(p);
		big = big.subtract(new BigInteger("1"));

		return big;
	}

	static boolean isPrime(int number)
	{
		/* loop through possible divisors. If at least one is evenly divisible,
		 * then the number is composite (ie. not prime). */
		
		for (int divisor = 2; divisor <= number / 2; divisor++)
		{
			if (number % divisor == 0)
			{
				// number is not a prime
				return false;
			}
		}
		// number is prime
		return true;
	}

}
