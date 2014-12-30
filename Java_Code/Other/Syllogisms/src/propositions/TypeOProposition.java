package propositions;

public class TypeOProposition extends Proposition
{
	public TypeOProposition(Term term1, Term term2)
	{
		super(term1, term2);
		
		super.beginning = "Some";
		super.copula = "are not";
		
		super.term1Distributed = false;
		super.term2Distributed = true;
		super.affirmative = false;
		super.universal = false;
	}
}
