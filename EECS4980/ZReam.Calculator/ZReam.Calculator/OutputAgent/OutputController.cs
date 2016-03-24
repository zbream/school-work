using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using ZReam.Calculator.Math;
using ZReam.Calculator.OutputAgent.Contracts;
using ZReam.Calculator.RootAgent.Contracts;


namespace ZReam.Calculator.OutputAgent
{
    class OutputController : IOutputController
    {
        IOutputPresentation presentation;
        IOutputAbstraction abstraction;

        IRootController root;
        
        public OutputController(IRootController root)
        {
            this.root = root;

            // initialize this agent
            presentation = new OutputPresentation();
            abstraction = new OutputAbstraction();
        }

        public UserControl GetUI()
        {
            return presentation.GetUI();
        }

        public void UpdateOutput(AST syntaxTree)
        {
            abstraction.CurrentOutput = syntaxTree;

            if (syntaxTree != null)
            {
                presentation.OutputTEX(syntaxTree.RenderOutputTEX());
                presentation.OutputSpeech(syntaxTree.RenderOutputSpeech());
            }
        }

        public void RepeatOutput()
        {
            AST syntaxTree = abstraction.CurrentOutput;

            if (syntaxTree != null)
            {
                presentation.OutputSpeech(syntaxTree.RenderOutputSpeech());
            }
        }
    }
}
