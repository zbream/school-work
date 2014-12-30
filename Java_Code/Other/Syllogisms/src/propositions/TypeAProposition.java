package propositions;

public class TypeAProposition extends Proposition
{
	public TypeAProposition(Term term1, Term term2)
	{
		super(term1, term2);
		
		super.beginning = "All";
		super.copula = "are";

		super.term1Distributed = true;
		super.term2Distributed = false;
		super.affirmative = true;
		super.universal = true;
	}

}
