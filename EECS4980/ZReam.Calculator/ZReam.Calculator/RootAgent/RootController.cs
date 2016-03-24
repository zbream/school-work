using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ZReam.Calculator.RootAgent
{
    class RootController
    {
        public void Initialize()
        {
            RootPresentation p = new RootPresentation();
            p.Show();

            IEnumerable<Math.Token> tokens = Math.Tokenizer.FromString("-(234----43)*-6=");
            Math.ASTNode tree = Math.ASTParser.ParseTree(tokens);
            Console.ReadKey(true);
        }
    }
}
