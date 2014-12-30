package syllogisms;

public class Form
{
	private String mood;
	private int figure;

	public Form(String form) throws InvalidForm
	{
		mood = form.substring(0, 3).toUpperCase();
		figure = Integer.parseInt(form.substring(form.length() - 1));

		// check for errors in Form format
		for (int x = 0; x <= 2; x++)
		{
			if ("AEIO".indexOf(mood.charAt(x)) == -1)
				throw new InvalidForm("Proposition " + (x + 1) + " is not of a valid Type (A,E,I,O).");
		}

		if (figure > 4)
		{
			throw new InvalidForm("Figure must be between 1-4.");
		}
	}

	@Override
	public String toString()
	{
		return mood + "-" + figure;
	}

	public String getMood()
	{
		return mood;
	}

	public int getFigure()
	{
		return figure;
	}

	public char getTypeOfMajor()
	{
		return mood.charAt(0);
	}

	public char getTypeOfMinor()
	{
		return mood.charAt(1);
	}

	public char getTypeOfConclusion()
	{
		return mood.charAt(2);
	}

	public char getTypeAtProposition(int proposition)
	{
		return mood.charAt(proposition);
	}
}
