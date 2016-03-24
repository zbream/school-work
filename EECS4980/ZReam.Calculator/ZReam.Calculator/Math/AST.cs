using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZReam.Calculator.Math
{
    public class AST
    {
        private ASTNode root;

        public AST(ASTNode rootNode)
        {
            this.root = rootNode;
        }

        public long Result()
        {
            return (getValue(root));
        }

        public string RenderOutputTEX()
        {
            return string.Format("$$ {0} = {1} $$", getTEX(root, null), Result());
        }

        public string RenderOutputSpeech()
        {
            string resultString;
            long result = Result();
            if (result < 0)
            {
                resultString = "negative " + (-1 * result);
            }
            else
            {
                resultString = "" + result;
            }

            return string.Format("{0} , equals {1}", getSpeech(root, null), resultString);
        }

        private static long getValue(ASTNode node)
        {
            switch(node.Token.Type)
            {
                case TokenType.TExponent:
                    return (long)System.Math.Pow(getValue(node.Left), getValue(node.Right));
                case TokenType.TNegative:
                    return (-1 * getValue(node.Left));
                case TokenType.TMultiply:
                    return (getValue(node.Left) * getValue(node.Right));
                case TokenType.TAdd:
                    return (getValue(node.Left) + getValue(node.Right));
                case TokenType.TSubtract:
                    return (getValue(node.Left) - getValue(node.Right));
                case TokenType.TNumber:
                default:
                    return node.Token.Value;
            }
        }

        private static string getTEX(ASTNode node, Token parentToken)
        {
            string format = "{0}";
            if (parentToken != null)
            {
                if (node.Token.IsOperator() && (node.Token.OperatorPrecedence() < parentToken.OperatorPrecedence()))
                {
                    format = "( {0} )";
                }
            }

            string value = string.Empty;
            switch (node.Token.Type)
            {                
                case TokenType.TExponent:
                    value = string.Format("{0} ^{{ {1} }}", getTEX(node.Left, node.Token), getTEX(node.Right, null));
                    break;
                case TokenType.TNegative:
                    value = string.Format("-{0}", getTEX(node.Left, node.Token));
                    break;
                case TokenType.TMultiply:
                    value = string.Format("{0} * {1}", getTEX(node.Left, node.Token), getTEX(node.Right, node.Token));
                    break;
                case TokenType.TAdd:
                    value = string.Format("{0} + {1}", getTEX(node.Left, node.Token), getTEX(node.Right, node.Token));
                    break;
                case TokenType.TSubtract:
                    value = string.Format("{0} - {1}", getTEX(node.Left, node.Token), getTEX(node.Right, node.Token));
                    break;
                case TokenType.TNumber:
                default:
                    value = node.Token.Value.ToString();
                    break;
            }

            return string.Format(format, value);
        }

        private static string getSpeech(ASTNode node, Token parentToken)
        {
            string format = "{0}";
            if (parentToken != null)
            {
                if (node.Token.IsOperator() && (node.Token.OperatorPrecedence() < parentToken.OperatorPrecedence()))
                {
                    format = ", quantity {0} end quantity ,";
                }
            }

            string value = string.Empty;
            switch (node.Token.Type)
            {
                case TokenType.TExponent:
                    value = string.Format("{0} to the power of {1}", getSpeech(node.Left, node.Token), getSpeech(node.Right, node.Token));
                    break;
                case TokenType.TNegative:
                    value = string.Format("negative {0}", getSpeech(node.Left, node.Token));
                    break;
                case TokenType.TMultiply:
                    value = string.Format("{0} times {1}", getSpeech(node.Left, node.Token), getSpeech(node.Right, node.Token));
                    break;
                case TokenType.TAdd:
                    value = string.Format("{0} plus {1}", getSpeech(node.Left, node.Token), getSpeech(node.Right, node.Token));
                    break;
                case TokenType.TSubtract:
                    value = string.Format("{0} minus {1}", getSpeech(node.Left, node.Token), getSpeech(node.Right, node.Token));
                    break;
                case TokenType.TNumber:
                default:
                    value = node.Token.Value.ToString();
                    break;
            }

            return string.Format(format, value);
        }
    }
}
