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
        IInputPresentation presentation;
        IInputAbstraction abstraction;

        IRootController root;

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

        private void SubmitInput()
        {
            root.NewInput(abstraction.CurrentInputString);
        }

        private SpeechRecognitionEngine speechRecognition;

        private void InitializeSpeechRecognition()
        {
            speechRecognition = new SpeechRecognitionEngine();
            speechRecognition.SetInputToDefaultAudioDevice();
            //speechRecognition.SetInputToWaveFile(@"D:\Users\Zack\Desktop\t.wav");

            // math grammar
            Grammar math;
            using (Stream stream = Grammars.EmbeddedGrammars.MathCompiled)
            {
                math = new Grammar(stream);
            }
            speechRecognition.LoadGrammar(math);

            // wire necessary events
            abstraction.PropertyChanged += (sender, e) => { if (e.PropertyName.Equals(nameof(abstraction.IsSpeechEnabled))) SpeechEnabledChanged(); };
            speechRecognition.SpeechRecognized += SpeechRecognition_SpeechRecognized;
            speechRecognition.SpeechHypothesized += SpeechRecognition_SpeechHypothesized;
            speechRecognition.SpeechRecognitionRejected += SpeechRecognition_SpeechRecognitionRejected;

            SpeechEnabledChanged();
        }

        private void SpeechEnabledChanged()
        {
            if (abstraction.IsSpeechEnabled)
            {
                speechRecognition.RecognizeAsync(RecognizeMode.Multiple);
            }
            else
            {
                speechRecognition.RecognizeAsyncCancel();
            }
        }

        private void SpeechRecognition_SpeechHypothesized(object sender, SpeechHypothesizedEventArgs e)
        {
            abstraction.CurrentInputString = e.Result.Text;
        }

        private void SpeechRecognition_SpeechRecognitionRejected(object sender, SpeechRecognitionRejectedEventArgs e)
        {
            abstraction.CurrentInputString = string.Empty;
        }

        private void SpeechRecognition_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            abstraction.CurrentInputString = e.Result.Semantics.Value.ToString();
            SubmitInput();
        }

        
    }
}
