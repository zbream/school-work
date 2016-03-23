// 3550 Programming Asignment ZackReam JordanKlamut

using System;
using System.IO;
using Jaz.JazExecutor;
using Jaz.JazMachine;
using Jaz.JazParser;

namespace Jaz
{
    class Program
    {
        static void Main(string[] args)
        {
            // get path of input
            string inputPath;
            if(args.Length > 0)
            {
                inputPath = args[0];
            }
            else
            {
                Console.WriteLine("JAZ Interpreter - EECS 3550 Programming Assignment");
                Console.WriteLine("Zack Ream , Jordan Klamut");
                Console.Write("\nEnter path to a jaz file: ");
                inputPath = Console.ReadLine();
                Console.WriteLine("==========");
            }
            
            try
            {
                Executor executor = new Executor();

                // parse commands
                using (StreamReader stream = File.OpenText(inputPath))
                {
                    Parser.ParseProgram(executor, stream);
                }

                // run program
                Machine machine = new Machine();
                executor.Execute(machine);
            }
            catch (IOException)
            {
                Console.WriteLine("Unable to open input file.");
                return;
            }
            catch (ParseException ex)
            {
                Console.WriteLine("Parse Error: {0}", ex.Message);
                return;
            }
            catch (ExecuteException ex)
            {
                Console.WriteLine("Execute Error: {0}", ex.Message);
                return;
            }
        }
    }
}
