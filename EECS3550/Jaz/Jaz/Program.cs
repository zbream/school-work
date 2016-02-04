using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazExecutor;
using Jaz.JazMachine;
using Jaz.JazParser;

namespace Jaz
{
    class Program
    {
        // TEST inputs
        const string test = @"test.txt";
        const string INPUT_DEMO = @"Inputs\demo.jaz";
        const string INPUT_FACTPROC = @"Inputs\factProc.jaz";
        const string INPUT_FOO = @"Inputs\foo.jaz";
        const string INPUT_RECTFACT = @"Inputs\rectFact.jaz";

        static void Main(string[] args)
        {
            Executor executor = new Executor();

            // parse commands
            using (StreamReader stream = File.OpenText(test))
            {
                Parser.ParseProgram(executor, stream);
            }

            // run program
            Machine machine = new Machine();
            executor.Execute(machine);

            Console.WriteLine("\n==========\nProgram Finished. Press a key...");
            Console.ReadKey(true);
        }
    }
}
