import java.math.BigInteger;
import java.util.Scanner;


public class FactorialApp
{

	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		System.out.println("Enter a number to find the factorial of (using a recursive algorithm).");
		String num = input.next();
		
		System.out.println(factorial(new BigInteger(num)));
	}

	static BigInteger factorial(BigInteger n)
	{
		if(n.compareTo(new BigInteger("0")) == 0)
		{
			return new BigInteger("1");
		}
		else
		{
			return n.multiply(factorial(n.subtract(new BigInteger("1"))));
		}
		
	}
	
}
