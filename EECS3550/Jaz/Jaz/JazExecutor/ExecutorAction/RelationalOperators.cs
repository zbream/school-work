using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.RelationalOperators
{
    class EAne : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            int result = (b != a) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return "<>";
        }
    }

    class EAle : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            int result = (b <= a) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return "<=";
        }
    }

    class EAge : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            int result = (b >= a) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return ">=";
        }
    }

    class EAlt : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            int result = (b < a) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return "<";
        }
    }

    class EAgt : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            int result = (b > a) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return ">";
        }
    }

    class EAeq : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            int result = (b == a) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return "=";
        }
    }
}
