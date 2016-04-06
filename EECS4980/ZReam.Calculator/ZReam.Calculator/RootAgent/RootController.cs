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
        
        public RootController()
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

            // show the window
            presentation.RegisterOnClose((sender, e) => { Shutdown(); });
            presentation.ShowUI();
        }

        public void Shutdown()
        {
            Application.Current.Shutdown(0);
        }

        public void ToggleSpeechInput(bool enable)
        {
            input.ToggleSpeech(enable);
        }

        public void ToggleSpeechOutput(bool enable)
        {
            output.ToggleSpeech(enable);
        }

        public void Calculate(string inputString)
        {
            string outputVisible, outputAudible;

            try
            {
                var tokens = MathHandler.Tokenizer.FromString(inputString);
                var tree = MathHandler.ASTParser.ParseTree(tokens);

                outputVisible = tree.RenderOutputTEX();
                outputAudible = tree.RenderOutputSpeech();
            }
            catch (MathHandler.ParseException)
            {
                outputVisible = "Parse Error: invalid grammar";
                outputAudible = "Parsing error, invalid grammar";
            }
            catch (InvalidOperationException)
            {
                // probably a stack error, which means invalid operator use
                outputVisible = "Parse Error: invalid grammar";
                outputAudible = "Parsing error, invalid grammar";
            }
            catch (OverflowException)
            {
                outputVisible = "Math Error: overflow";
                outputAudible = "Math error, overflow";
            }

            output.UpdateOutput(outputVisible, outputAudible);
        }

        public void RepeatOutput()
        {
            output.RepeatSpeech();
        }
    }
}
