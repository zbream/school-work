using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.ArithmeticOperators
{
    class EAadd : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            machine.Stack.Push(b + a);

            return true;
        }

        public override string ToString()
        {
            return "+";
        }
    }

    class EAsub : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            machine.Stack.Push(b - a);

            return true;
        }

        public override string ToString()
        {
            return "-";
        }
    }

    class EAmul : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            machine.Stack.Push(b * a);

            return true;
        }

        public override string ToString()
        {
            return "*";
        }
    }

    class EAdiv : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            machine.Stack.Push((int)(b / a));

            return true;
        }

        public override string ToString()
        {
            return "/";
        }
    }

    class EAmod : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = (int)machine.Stack.Pop();
            int b = (int)machine.Stack.Pop();

            machine.Stack.Push(b % a);

            return true;
        }

        public override string ToString()
        {
            return "div";
        }
    }
}
