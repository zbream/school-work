using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Speech.Recognition;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

using ZReam.Calculator.InputAgent.Contracts;
using ZReam.Calculator.RootAgent.Contracts;

namespace ZReam.Calculator.InputAgent
{
    class InputController : IInputController
    {
        private const string GRAMMAR_MATH = "Math";
        private const string GRAMMAR_COMMANDS = "Commands";

        private IInputPresentation presentation;
        private IInputAbstraction abstraction;
        private IRootController root;

        private SpeechRecognitionEngine speechRecognition;

        public InputController(IRootController root)
        {
            this.root = root;

            // initialize this agent
            abstraction = new InputAbstraction(SubmitInput);
            presentation = new InputPresentation();
            presentation.GetUI().DataContext = abstraction;

            InitializeSpeechRecognition();
        }

        public UserControl GetUI()
        {
            return presentation.GetUI();
        }

        public void ToggleSpeech(bool enable)
        {
            abstraction.IsSpeechEnabled = enable;
        }

        private void SubmitInput()
        {
            root.Calculate(abstraction.CurrentInputString);
        }
        
        private void InitializeSpeechRecognition()
        {
            speechRecognition = new SpeechRecognitionEngine();
            speechRecognition.SetInputToDefaultAudioDevice();
            //speechRecognition.SetInputToWaveFile(@"D:\Users\Zack\Desktop\t.wav");

            // math grammar
            using (Stream stream = Resources.Grammars.EmbeddedGrammars.MathCompiled)
            {
                Grammar math = new Grammar(stream) { Name = GRAMMAR_MATH };
                speechRecognition.LoadGrammar(math);
            }

            // commands grammar
            using (Stream stream = Resources.Grammars.EmbeddedGrammars.CommandsCompiled)
            {
                Grammar commands = new Grammar(stream) { Name = GRAMMAR_COMMANDS };
                speechRecognition.LoadGrammar(commands);
            }

            // wire necessary events
            speechRecognition.SpeechRecognized += SpeechRecognition_SpeechRecognized;
            speechRecognition.SpeechHypothesized += SpeechRecognition_SpeechHypothesized;
            speechRecognition.SpeechRecognitionRejected += SpeechRecognition_SpeechRecognitionRejected;
            abstraction.PropertyChanged += (sender, e) => 
            {
                if (e.PropertyName.Equals(nameof(abstraction.IsSpeechEnabled))) SpeechEnabledChanged();
            };

            speechRecognition.RecognizeAsync(RecognizeMode.Multiple);
        }

        private void SpeechEnabledChanged()
        {
            if (!abstraction.IsSpeechEnabled)
            {
                abstraction.CurrentInputString = string.Empty;
            }
        }

        private void SpeechRecognition_SpeechHypothesized(object sender, SpeechHypothesizedEventArgs e)
        {
            if (abstraction.IsSpeechEnabled)
            {
                if (e.Result.Grammar.Name.Equals(GRAMMAR_MATH))
                {
                    abstraction.CurrentInputString = e.Result.Text;
                }
                else
                {
                    abstraction.CurrentInputString = string.Empty;
                }
            }
        }

        private void SpeechRecognition_SpeechRecognitionRejected(object sender, SpeechRecognitionRejectedEventArgs e)
        {
            if (abstraction.IsSpeechEnabled)
            {
                abstraction.CurrentInputString = string.Empty;
            }
        }

        private void SpeechRecognition_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            if (abstraction.IsSpeechEnabled)
            {
                switch (e.Result.Grammar.Name)
                {
                    case GRAMMAR_MATH:
                        abstraction.CurrentInputString = e.Result.Semantics.Value.ToString();
                        SubmitInput();
                        break;
                    case GRAMMAR_COMMANDS:
                        abstraction.CurrentInputString = string.Empty;
                        switch (e.Result.Semantics["command"].Value.ToString())
                        {
                            case "repeat":
                                root.RepeatOutput();
                                break;
                            case "exit":
                                root.Shutdown();
                                break;
                            case "mode":
                                {
                                    bool enable = (e.Result.Semantics["onoff"].Value.Equals("on"));
                                    if (e.Result.Semantics["inout"].Value.Equals("in"))
                                    {
                                        root.ToggleSpeechInput(enable);
                                    }
                                    else
                                    {
                                        root.ToggleSpeechOutput(enable);
                                    }
                                }
                                break;
                        }
                        break;
                }
            }
            else
            {
                // only allow enabling speech input
                if (e.Result.Grammar.Name.Equals(GRAMMAR_COMMANDS)
                    && e.Result.Semantics["command"].Value.Equals("mode")
                    && e.Result.Semantics["inout"].Value.Equals("in")
                    && e.Result.Semantics["onoff"].Value.Equals("on"))
                {
                    root.ToggleSpeechInput(true);
                }
            }
        }
    }
}
