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

            IEnumerable<Math.Token> tokens = Math.Tokenizer.FromString("-(5+7)*3^2");
            Math.AST tree = Math.ASTParser.ParseTree(tokens);
            long result = tree.Result();
            string TeX = tree.RenderOutputTEX();
            string Speech = tree.RenderOutputSpeech();
            Console.ReadKey(true);
        }
    }
}
