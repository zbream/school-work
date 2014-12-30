package syllogisms;

import propositions.Proposition;
import propositions.Term;

public class Argument
{
	final String majorTerm = "P";
	final String minorTerm = "S";
	final String middleTerm = "M";

	private Proposition major, minor, conclusion;

	private Form form;

	public Argument(Form form) throws InvalidForm
	{
		this.form = form;
		Term[][] terms = new Term[3][2];

		if (form.getFigure() % 2 == 1) // 1 or 3
		{
			terms[0][0] = new Term(middleTerm);
			terms[0][1] = new Term(majorTerm);
		} else
		{
			terms[0][0] = new Term(majorTerm);
			terms[0][1] = new Term(middleTerm);
		}

		if (form.getFigure() / 3 == 0) // 1 or 2
		{
			terms[1][0] = new Term(minorTerm);
			terms[1][1] = new Term(middleTerm);
		} else
		{
			terms[1][0] = new Term(middleTerm);
			terms[1][1] = new Term(minorTerm);
		}

		terms[2][0] = new Term(minorTerm);
		terms[2][1] = new Term(majorTerm);

		major = Proposition.makeProposition(form.getTypeOfMajor(), terms[0][0], terms[0][1]);
		minor = Proposition.makeProposition(form.getTypeOfMinor(), terms[1][0], terms[1][1]);
		conclusion = Proposition.makeProposition(form.getTypeOfConclusion(), terms[2][0], terms[2][1]);
	}

	public Argument(String formString) throws InvalidForm
	{
		this(new Form(formString));
	}

	// number ranges from 1 (AAA-1) to 256 (OOO-4)
	public Argument(int number) throws InvalidForm
	{
		this(Argument.formFromNumber(number));
	}

	static private Form formFromNumber(int number) throws InvalidForm
	{
		String types = "AEIO";
		int counter = 0;

		for (int majorTypeIndex = 0; majorTypeIndex < 4; majorTypeIndex++)
		{
			for (int minorTypeIndex = 0; minorTypeIndex < 4; minorTypeIndex++)
			{
				for (int conclusionTypeIndex = 0; conclusionTypeIndex < 4; conclusionTypeIndex++)
				{
					for (int figure = 1; figure <= 4; figure++)
					{
						counter++;
						if (counter == number)
						{
							char majorType = types.charAt(majorTypeIndex);
							char minorType = types.charAt(minorTypeIndex);
							char conclusionType = types.charAt(conclusionTypeIndex);
							return (new Form("" + majorType + minorType + conclusionType + "-" + figure));
						}
					}
				}
			}
		}
		throw new InvalidForm("No form is at position " + number + ".");
	}

	public String getForm()
	{
		return form.toString();
	}
	
	public Proposition getMajor()
	{
		return major;
	}

	public Proposition getMinor()
	{
		return minor;
	}

	public Proposition getConclusion()
	{
		return conclusion;
	}

	@Override
	public String toString()
	{
		return " " + major.toString() + "\n " + minor.toString() + "\n\u2234" + conclusion.toString();
	}

}
