using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using ZReam.Calculator.OutputAgent;
using ZReam.Calculator.OutputAgent.Contracts;
using ZReam.Calculator.RootAgent.Contracts;

namespace ZReam.Calculator.RootAgent
{
    class RootController : IRootController
    {
        private IRootPresentation presentation;
        private IRootAbstraction abstraction;

        private IOutputController output;

        public void Initialize()
        {
            // initialize this agent
            presentation = new RootPresentation();
            abstraction = new RootAbstraction();

            // initialize output agent
            output = new OutputController(this);
            presentation.SetOutputUI(output.GetUI());

            // do math example
            //IEnumerable<Math.Token> tokens = Math.Tokenizer.FromString("-(5+7)*3^2");
            IEnumerable<Math.Token> tokens = Math.Tokenizer.FromString("(5+7)*(3+2)");
            Math.AST tree = Math.ASTParser.ParseTree(tokens);

            // show the window
            presentation.ShowInterface();
            output.UpdateOutput(tree);
        }
    }
}
