import java.util.Scanner;

public class Quadratic
{
	/* Zack Ream
	 * Ex8.10 - Algebra: Quadratic Equations
	 * 
	 * This program accepts input for three coefficients of a quadratic
	 * equation. It returns that equation's roots, if they exist. */
	
	public static void main(String[] args)
	{
		// initialize variables, scanner for input
		double inputA, inputB, inputC;
		Scanner input = new Scanner(System.in);

		// prompt for and accept input of variables a,b,c
		System.out.println("Solve Ax^2 + Bx + C = 0");
		System.out.print(" Enter values for coefficients A,B,C: ");
		inputA = input.nextDouble();
		inputB = input.nextDouble();
		inputC = input.nextDouble();
		// separate output from input
		System.out.println();

		// create new QuadraticEquation, using variables in constructor
		QuadraticEquation QE = new QuadraticEquation(inputA, inputB, inputC);

		// check discriminant, to see number of roots
		double discriminant = QE.getDiscriminant();
		if (discriminant < 0)
		{
			// discriminant is negative, no roots
			System.out.println("The equation has no real roots.");
		} else if (discriminant == 0)
		{
			// discriminant is 0, one root
			System.out.print("The equation has one root:\n ");
			System.out.println(QE.getRoot1());
		} else
		{
			// discriminant is positive, two roots
			System.out.print("The equation has two roots:\n ");
			System.out.print(QE.getRoot1() + "\n ");
			System.out.println(QE.getRoot2());
		}

		input.close();
	}

}

class QuadraticEquation
{
	// initialize data fields a,b,c
	private double a, b, c;

	// constructor method
	public QuadraticEquation(double newA, double newB, double newC)
	{
		a = newA;
		b = newB;
		c = newC;
	}

	// get methods, to return the values a b and c
	public double getA()
	{
		return a;
	}

	public double getB()
	{
		return b;
	}

	public double getC()
	{
		return c;
	}

	// method to return discriminant, (b^2)-4ac
	public double getDiscriminant()
	{
		double discriminant = Math.pow(b, 2) - (4 * a * c);
		return discriminant;
	}

	// method to return root 1, which uses +
	public double getRoot1()
	{
		double root;
		root = (-b + Math.sqrt(getDiscriminant())) / (2 * a);
		return root;
	}

	// method to return root 2, which uses -
	public double getRoot2()
	{
		double root;
		root = (-b - Math.sqrt(getDiscriminant())) / (2 * a);
		return root;
	}
}
