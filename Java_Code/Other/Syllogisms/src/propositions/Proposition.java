package propositions;

import syllogisms.InvalidForm;

public abstract class Proposition
{
	public static Proposition makeProposition(char type, Term term1, Term term2) throws InvalidForm
	{
		switch (type)
		{
		case 'A':
			return new TypeAProposition(term1, term2);
		case 'E':
			return new TypeEProposition(term1, term2);
		case 'I':
			return new TypeIProposition(term1, term2);
		case 'O':
			return new TypeOProposition(term1, term2);
		default:
			throw new InvalidForm();
		}
	}

	protected Proposition(Term term1, Term term2)
	{
		this.term1 = term1;
		this.term2 = term2;
	}
	
	protected String beginning, copula;

	protected Term term1, term2;

	public Term getTerm1()
	{
		return this.term1;
	}

	public Term getTerm2()
	{
		return this.term2;
	}

	protected boolean term1Distributed, term2Distributed;

	public boolean isTerm1Distributed()
	{
		return term1Distributed;
	}

	public boolean isTerm2Distributed()
	{
		return term2Distributed;
	}

	protected boolean universal, affirmative;

	// Quantity: true if universal, false if particular
	public boolean isUniversal()
	{
		return universal;
	}

	// Quality: true if affirmative, false if negative
	public boolean isAffirmative()
	{
		return affirmative;
	}

	@Override
	public String toString()
	{
		return beginning + " " + term1.toString() + " " + copula + " " + term2.toString() + ".";
	}
}
