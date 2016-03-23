// 3550 Programming Asignment ZackReam JordanKlamut

using System;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.Output
{
    class EAprint : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            string value = machine.Stack.PeekString();
            Console.WriteLine(value);

            return true;
        }

        public override string ToString()
        {
            return "print";
        }
    }

    class EAshow : IExecutorAction
    {
        public EAshow(string rval)
        {
            this.value = rval;
        }

        private string value;

        public bool Perform(Machine machine)
        {
            Console.WriteLine(value);

            return true;
        }

        public override string ToString()
        {
            return "show " + value;
        }
    }
}
