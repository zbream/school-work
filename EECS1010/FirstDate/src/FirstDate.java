public class FirstDate
{
	/* Zack Ream
	 * First Date
	 * 
	 * This program accepts input for two dates, and returns which of the dates
	 * came first, chronologically. */
	public static void main(String[] args)
	{
		// Initialize variables, input values
		int month1, day1, year1, month2, day2, year2;
		month1 = 7;
		day1 = 21;
		year1 = 1993;
		month2 = 8;
		day2 = 21;
		year2 = 1993;
		int first;

		if (year1 < year2)
			first = 1;
		else if (year1 > year2)
			first = 2;
		else if (month1 < month2)
			first = 1;
		else if (month1 > month2)
			first = 2;
		else if (day1 < day2)
			first = 1;
		else if (day1 > day2)
			first = 2;
		else
			first = 0;

		if (first == 0)
			System.out.println("The dates are the same.");
		else
			System.out.println("Date " + first + " came first.");
	}
}
