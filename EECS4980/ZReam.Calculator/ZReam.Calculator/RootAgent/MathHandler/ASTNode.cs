using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZReam.Calculator.RootAgent.MathHandler
{
    public class ASTNode
    {
        public ASTNode(Token token, ASTNode left, ASTNode right)
        {
            this.Token = token;
            this.Left = left;
            this.Right = right;
        }

        public Token Token { get; }

        public ASTNode Left { get; }

        public ASTNode Right { get; }

        public override string ToString()
        {
            return Token.ToString();
        }
    }
}
