// 3550 Programming Asignment ZackReam JordanKlamut

using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.RelationalOperators
{
    class EAne : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            int result = (b != a) ? 1 : 0;
            machine.Stack.PushInt(result);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            int result = (b <= a) ? 1 : 0;
            machine.Stack.PushInt(result);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            int result = (b >= a) ? 1 : 0;
            machine.Stack.PushInt(result);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            int result = (b < a) ? 1 : 0;
            machine.Stack.PushInt(result);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            int result = (b > a) ? 1 : 0;
            machine.Stack.PushInt(result);

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
            int a = machine.Stack.PopInt();
            int b = machine.Stack.PopInt();

            int result = (b == a) ? 1 : 0;
            machine.Stack.PushInt(result);

            return true;
        }

        public override string ToString()
        {
            return "=";
        }
    }
}
