using System.Collections.Generic;

namespace ZReam.Calculator.RootAgent.MathHandler
{
    class ASTParser
    {
        public static AST ParseTree(IEnumerable<Token> tokens)
        {
            return new AST(new ASTParser().parse(tokens));
        }

        private ASTParser() { }
        private Stack<Token> operatorStack = new Stack<Token>();
        private Stack<ASTNode> outputStack = new Stack<ASTNode>();

        private ASTNode parse(IEnumerable<Token> tokens)
        {
            foreach (Token token in tokens)
            {
                switch (token.Type)
                {
                    case TokenType.TNumber:
                        addLeafNode(token);
                        break;
                    case TokenType.TOpenParenthesis:
                        operatorStack.Push(token);
                        break;
                    case TokenType.TCloseParenthesis:
                        handleCloseParenthesis();
                        break;
                    default:
                        if (token.IsOperator())
                        {
                            handleOperator(token);
                        }
                        else
                        {
                            // handle equals
                        }
                        break;
                }
            }

            while (operatorStack.Count > 0)
            {
                addOperatorNode(operatorStack.Pop());
            }

            return outputStack.Pop();
        }

        private void handleOperator(Token o1)
        {
            Token o2;

            while (operatorStack.Count > 0 && (o2 = operatorStack.Peek()).IsOperator())
            {
                if ((!o1.OperatorIsRightAssociative() && o1.OperatorPrecedence() <= o2.OperatorPrecedence())
                    || (o1.OperatorIsRightAssociative() && o1.OperatorPrecedence() < o2.OperatorPrecedence())
                )
                {
                    operatorStack.Pop();
                    addOperatorNode(o2);
                }
                else
                {
                    break;
                }
            }

            operatorStack.Push(o1);
        }

        private void handleCloseParenthesis()
        {
            while (operatorStack.Count > 0)
            {
                Token popped = operatorStack.Pop();
                if (popped.Type == TokenType.TOpenParenthesis)
                {
                    return;
                }
                else
                {
                    addOperatorNode(popped);
                }
            }
            throw new ParseException("Unbalanced right parenthesis.");
        }

        private void addOperatorNode(Token op)
        {
            if (op.Type != TokenType.TNegative)
            {
                // binary operator
                ASTNode right = outputStack.Pop();
                ASTNode left = outputStack.Pop();
                outputStack.Push(new ASTNode(op, left, right));
            }
            else
            {
                // unary operator
                ASTNode left = outputStack.Pop();
                outputStack.Push(new ASTNode(op, left, null));
            }            
        }

        private void addLeafNode(Token op)
        {
            outputStack.Push(new ASTNode(op, null, null));
        }
    }
}
