package propositions;

public class TypeIProposition extends Proposition
{
	public TypeIProposition(Term term1, Term term2)
	{
		super(term1, term2);
		
		super.beginning = "Some";
		super.copula = "are";
		
		super.term1Distributed = false;
		super.term2Distributed = false;
		super.affirmative = true;
		super.universal = false;
	}
}
