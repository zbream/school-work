package propositions;

public class TypeEProposition extends Proposition
{
	public TypeEProposition(Term term1, Term term2)
	{
		super(term1, term2);
		
		super.beginning = "No";
		super.copula = "are";

		super.term1Distributed = true;
		super.term2Distributed = true;
		super.affirmative = false;
		super.universal = true;
	}
}
