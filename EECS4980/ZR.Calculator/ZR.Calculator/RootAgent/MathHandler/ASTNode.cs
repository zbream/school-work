namespace ZR.Calculator.RootAgent.MathHandler
{
    class ASTNode
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
