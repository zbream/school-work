using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using ZReam.Calculator.InputAgent;
using ZReam.Calculator.InputAgent.Contracts;
using ZReam.Calculator.OutputAgent;
using ZReam.Calculator.OutputAgent.Contracts;
using ZReam.Calculator.RootAgent.Contracts;

namespace ZReam.Calculator.RootAgent
{
    class RootController : IRootController
    {
        private IRootPresentation presentation;
        private IRootAbstraction abstraction;

        private IInputController input;
        private IOutputController output;
        
        public void Initialize()
        {
            // initialize this agent
            presentation = new RootPresentation();
            abstraction = new RootAbstraction();

            // initialize input agent
            input = new InputController(this);
            presentation.SetInputUI(input.GetUI());

            // initialize output agent
            output = new OutputController(this);
            presentation.SetOutputUI(output.GetUI());

            // do math example
            //IEnumerable<Math.Token> tokens = Math.Tokenizer.FromString("-(5+7)*3^2");
            //IEnumerable<Math.Token> tokens = Math.Tokenizer.FromString("(5+7)*(3+2)");
            //Math.AST tree = Math.ASTParser.ParseTree(tokens);

            // show the window
            presentation.ShowUI();
            //output.UpdateOutput(tree);
        }

        public void NewInput(string inputString)
        {
            var tokens = Math.Tokenizer.FromString(inputString);
            var tree = Math.ASTParser.ParseTree(tokens);

            output.UpdateOutput(tree);
        }
    }
}
