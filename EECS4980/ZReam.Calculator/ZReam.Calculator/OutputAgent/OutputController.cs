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
            abstraction = new OutputAbstraction();
            presentation = new OutputPresentation();
            presentation.GetUI().DataContext = abstraction;

            abstraction.IsSpeechEnabled = true;    
        }

        public UserControl GetUI()
        {
            return presentation.GetUI();
        }

        public void UpdateOutput(AST syntaxTree)
        {
            abstraction.CurrentOutput = syntaxTree;
            RepeatSpeech();
        }

        public void RepeatSpeech()
        {
            AST syntaxTree = abstraction.CurrentOutput;

            if (syntaxTree != null && abstraction.IsSpeechEnabled)
            {
                presentation.PlaySpeech(syntaxTree.RenderOutputSpeech());
            }
        }
    }
}
