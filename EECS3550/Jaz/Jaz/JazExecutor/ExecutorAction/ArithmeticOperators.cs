// 3550 Programming Asignment ZackReam JordanKlamut

using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.ArithmeticOperators
{
    class EAadd : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            machine.Stack.PushInt(b + a);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            machine.Stack.PushInt(b - a);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            machine.Stack.PushInt(b * a);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            machine.Stack.PushInt(b / a);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            machine.Stack.PushInt(b % a);

            return true;
        }

        public override string ToString()
        {
            return "div";
        }
    }
}
