using System;
using System.Collections.Generic;
using System.Linq;
using System.Speech.Synthesis;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using ZReam.Calculator.OutputAgent.Contracts;

namespace ZReam.Calculator.OutputAgent
{
    /// <summary>
    /// Interaction logic for OutputPresentation.xaml
    /// </summary>
    public partial class OutputPresentation : UserControl, IOutputPresentation
    {
        SpeechSynthesizer synthesizer;

        public OutputPresentation()
        {
            InitializeComponent();

            synthesizer = new SpeechSynthesizer();
        }

        public UserControl GetUI()
        {
            return this;
        }

        public void PlaySpeech(string text)
        {
            StopSpeech();
            synthesizer.SpeakAsync(text);
        }

        public void StopSpeech()
        {
            synthesizer.SpeakAsyncCancelAll();
        }

        private void ToggleButton_Unchecked(object sender, RoutedEventArgs e)
        {
            StopSpeech();
        }
    }
}
