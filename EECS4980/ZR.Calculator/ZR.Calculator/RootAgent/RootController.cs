using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using ZR.Calculator.InputAgent;
using ZR.Calculator.InputAgent.Contracts;
using ZR.Calculator.OutputAgent;
using ZR.Calculator.OutputAgent.Contracts;
using ZR.Calculator.RootAgent.Contracts;

namespace ZR.Calculator.RootAgent
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
                outputAudible = "Invalid grammar";
            }
            catch (InvalidOperationException)
            {
                // probably a stack error, which means invalid operator use
                outputVisible = "Parse Error: invalid grammar";
                outputAudible = "Invalid grammar";
            }
            catch (OverflowException)
            {
                outputVisible = "Math Error: overflow";
                outputAudible = "Overflow";
            }
            catch (Exception)
            {
                outputVisible = "Unknown Error";
                outputAudible = "Error";
            }

            output.UpdateOutput(outputVisible, outputAudible);
        }

        public void RepeatOutput()
        {
            output.RepeatSpeech();
        }
    }
}
