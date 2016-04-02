using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZReam.Calculator.RootAgent.MathHandler
{
    public class Token
    {
        public Token(TokenType type) : this(type, 0) { }

        public Token(TokenType type, long value)
        {
            this.Type = type;
            this.Value = value;
        }

        public TokenType Type { get; }

        public long Value { get; }

        public bool IsOperator()
        {
            switch (Type)
            {
                case TokenType.TAdd:
                case TokenType.TSubtract:
                case TokenType.TMultiply:
                case TokenType.TExponent:
                case TokenType.TNegative:
                    return true;
                default:
                    return false;
            }
        }

        public int OperatorPrecedence()
        {
            switch (Type)
            {
                case TokenType.TExponent:
                    return 5;
                case TokenType.TNegative:
                    return 4;
                case TokenType.TMultiply:
                    return 3;
                case TokenType.TAdd:
                case TokenType.TSubtract:
                    return 2;
                default:
                    throw new ParseException("Not an operator.");
            }
        }

        public bool OperatorIsRightAssociative()
        {
            if (IsOperator())
            {
                switch (Type)
                {
                    case TokenType.TExponent:
                    case TokenType.TNegative:
                        return true;
                    default:
                        return false;
                }
            }
            else
            {
                throw new ParseException("Not an operator.");
            }            
        }

        public override string ToString()
        {
            switch(Type)
            {
                case TokenType.TEquals:
                    return "=";
                case TokenType.TAdd:
                    return "+";
                case TokenType.TSubtract:
                    return "-";
                case TokenType.TMultiply:
                    return "*";
                case TokenType.TExponent:
                    return "^";
                case TokenType.TOpenParenthesis:
                    return "(";
                case TokenType.TCloseParenthesis:
                    return ")";
                case TokenType.TNegative:
                    return "N";
                case TokenType.TNumber:
                default:
                    return Value.ToString();
            }
        }
    }

    public enum TokenType
    {
        TNumber,
        TEquals,
        TAdd,
        TSubtract,
        TMultiply,
        TExponent,
        TOpenParenthesis,
        TCloseParenthesis,
        TNegative
    }
}
