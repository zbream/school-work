import java.util.Date;
import java.util.Scanner;

public class atmMain
{
	/* Zack Ream
	 * Ex10.7 - ATM Machine
	 * 
	 * This program runs an ATM machine holding 10 customers' accounts, allowing
	 * them to check balance, withdraw, and deposit funds. It is impossible to
	 * exit the program (users can always access their accounts). */

	static Account[] accountList;
	static Scanner input = new Scanner(System.in);

	public static void main(String[] args)
	{
		accountList = new Account[10];
		for (int x = 0; x < 10; x++)
		{
			accountList[x] = new Account(x, 100);
		}

		while (true) // main loop of ATM
		{
			int id, menuChoice;
			do // prompt for id until a valid choice is made
			{
				System.out.println("=================");
				System.out.print("Enter an id: ");
				id = input.nextInt();
			} while (id > (accountList.length - 1) || id < 0);
			do // use menu until account is exited
			{
				menuChoice = menu();
				execute(id, menuChoice);
			} while (menuChoice != 4);
			System.out.println();
		}

	}

	static int menu()
	{
		int choice;
		System.out.println("\nMain Menu");
		System.out.println("1: check balance");
		System.out.println("2: withdraw");
		System.out.println("3: deposit");
		System.out.println("4: exit");
		do // prompt for choice until a valid choice is made
		{
			System.out.print("Enter a choice: ");
			choice = input.nextInt();
		} while (choice > 4 || choice < 0);
		return choice;
	}

	static void execute(int id, int menuChoice)
	{
		switch (menuChoice)
		{
		case 1:
			System.out.printf("The balance is $%5.2f\n", accountList[id].getBalance());
			break;
		case 2:
			System.out.print("Enter an amount to withdraw: ");
			accountList[id].withdraw(input.nextDouble());
			break;
		case 3:
			System.out.print("Enter an amount to deposit: ");
			accountList[id].deposit(input.nextDouble());
			break;
		}
	}
}

class Account
{
	/* Zack Ream
	 * Ex8.7 - Account class
	 * 
	 * This class maintains balance information and methods for a bank account. */

	private int id;
	private double balance;
	private static double annualInterestRate = 0;
	private Date dateCreated = new Date();

	public Account(int newID, double newBalance)
	{
		this.id = newID;
		this.balance = newBalance;
	}

	public Account()
	{
		this(0, 0);

	}

	public int getID()
	{
		return this.id;
	}

	public double getBalance()
	{
		return this.balance;
	}

	public double getAnnualInterestRate()
	{
		return annualInterestRate;
	}

	public void setID(int newID)
	{
		this.id = newID;
	}

	public void setBalance(double newBalance)
	{
		this.balance = newBalance;
	}

	public void setAnnualInterestRate(double newAnnualInterestRate)
	{
		annualInterestRate = newAnnualInterestRate;
	}

	public Date getDateCreated()
	{
		return this.dateCreated;
	}

	public double getMonthlyInterestRate()
	{
		return annualInterestRate / 12;
	}

	public double getMonthlyInterest()
	{
		return this.balance * this.getMonthlyInterestRate();
	}

	public void withdraw(double amount)
	{
		this.balance -= amount;
	}

	public void deposit(double amount)
	{
		this.balance += amount;
	}
}