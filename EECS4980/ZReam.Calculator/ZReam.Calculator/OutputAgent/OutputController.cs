using System;
using System.Collections.Generic;
using System.Linq;
using System.Speech.Synthesis;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

using ZReam.Calculator.OutputAgent.Contracts;
using ZReam.Calculator.RootAgent.Contracts;

namespace ZReam.Calculator.OutputAgent
{
    class OutputController : IOutputController
    {
        private IOutputPresentation presentation;
        private IOutputAbstraction abstraction;
        private IRootController root;

        private SpeechSynthesizer speechSynthesizer;
        
        public OutputController(IRootController root)
        {
            this.root = root;
            
            // initialize this agent
            abstraction = new OutputAbstraction();
            presentation = new OutputPresentation();
            presentation.GetUI().DataContext = abstraction;

            InitializeSpeechSynthesis();
        }

        public UserControl GetUI()
        {
            return presentation.GetUI();
        }

        public void ToggleSpeech(bool enable)
        {
            abstraction.IsSpeechEnabled = enable;
        }

        public void UpdateOutput(string outputVisible, string outputAudible)
        {
            abstraction.CurrentOutputVisible = outputVisible;
            abstraction.CurrentOutputAudible = outputAudible;
            RepeatSpeech();
        }

        public void RepeatSpeech()
        {
            if (abstraction.IsSpeechEnabled && !string.IsNullOrWhiteSpace(abstraction.CurrentOutputAudible))
            {
                PlaySpeech(abstraction.CurrentOutputAudible);
            }
        }

        private void InitializeSpeechSynthesis()
        {
            speechSynthesizer = new SpeechSynthesizer();

            // wire necessary events
            abstraction.PropertyChanged += (sender, e) =>
            {
                if (e.PropertyName.Equals(nameof(abstraction.IsSpeechEnabled))) SpeechEnabledChanged();
            };
        }

        private void SpeechEnabledChanged()
        {
            if (!abstraction.IsSpeechEnabled)
            {
                StopSpeech();
            }
        }

        private void PlaySpeech(string text)
        {
            StopSpeech();
            speechSynthesizer.SpeakAsync(text);
        }

        private void StopSpeech()
        {
            speechSynthesizer.SpeakAsyncCancelAll();
        }
    }
}
