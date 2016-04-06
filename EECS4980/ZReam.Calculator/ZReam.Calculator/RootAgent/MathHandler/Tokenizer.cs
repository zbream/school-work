using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace ZReam.Calculator.RootAgent.MathHandler
{
    static class Tokenizer
    {
        const string REGEX_NUMBER = "[0-9]+";

        public static IEnumerable<Token> FromString(string input)
        {
            var tokens = new List<Token>();

            // a minus is...
            // binary: follows operand or right parenthesis
            // unary: follows operator or left parenthesis
            bool isMinusUnary = true;

            // parse each character
            int i = 0;
            while (i < input?.Length)
            {
                switch (input[i])
                {
                    case '+':
                        tokens.Add(new Token(TokenType.TAdd));
                        isMinusUnary = true;
                        break;
                    case '-':
                        tokens.Add(new Token(
                            isMinusUnary ? TokenType.TNegative : TokenType.TSubtract));
                        isMinusUnary = true;
                        break;
                    case '*':
                        tokens.Add(new Token(TokenType.TMultiply));
                        isMinusUnary = true;
                        break;
                    case '^':
                        tokens.Add(new Token(TokenType.TExponent));
                        isMinusUnary = true;
                        break;
                    case '(':
                        tokens.Add(new Token(TokenType.TOpenParenthesis));
                        isMinusUnary = true;
                        break;
                    case ')':
                        tokens.Add(new Token(TokenType.TCloseParenthesis));
                        isMinusUnary = false;
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        // we found a digit already, this WILL have a match
                        string numString = Regex.Match(input.Substring(i), REGEX_NUMBER).Value;

                        // add the token
                        long num = long.Parse(numString);
                        tokens.Add(new Token(TokenType.TNumber, num));

                        i += numString.Length;
                        isMinusUnary = false;
                        continue;
                    case '=':
                        tokens.Add(new Token(TokenType.TEquals));
                        isMinusUnary = true;
                        break;
                    case ' ':
                        break;
                    default:
                        throw new ParseException(string.Format("Invalid character, '{0}'.", input[i]));
                }

                // next character
                ++i;
            }

            return tokens;
        }
    }
}
