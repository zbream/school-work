using System;
using System.IO;
using System.Linq;
using System.Windows;

namespace ZReam.Calculator
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        const string SRGS_INPUT = "Math.grxml";
        const string SRGS_OUTPUT = "Math.cfg";

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            // compile human-readable grxml grammar into binary cfg grammar
            if (e.Args.Contains("-srgs", StringComparer.InvariantCultureIgnoreCase) && File.Exists(SRGS_INPUT))
            {
                using (Stream outStream = File.Create(SRGS_OUTPUT))
                {
                    System.Speech.Recognition.SrgsGrammar.SrgsGrammarCompiler.Compile(SRGS_INPUT, outStream);
                }
                Shutdown(0);
            }

            new RootAgent.RootController().Initialize();
        }
    }
}
