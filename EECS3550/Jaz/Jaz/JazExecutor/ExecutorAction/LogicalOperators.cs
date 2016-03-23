// 3550 Programming Asignment ZackReam JordanKlamut

using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.LogicalOperators
{
    class EAand : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            bool a = (machine.Stack.PopInt() != 0);
            bool b = (machine.Stack.PopInt() != 0);

            int result = (a && b) ? 1 : 0;
            machine.Stack.PushInt(result);

            return true;
        }

        public override string ToString()
        {
            return "&";
        }
    }

    class EAnot : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            bool a = (machine.Stack.PopInt() != 0);

            int result = (!a) ? 1 : 0;
            machine.Stack.PushInt(result);

            return true;
        }

        public override string ToString()
        {
            return "!";
        }
    }

    class EAor : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            bool a = (machine.Stack.PopInt() != 0);
            bool b = (machine.Stack.PopInt() != 0);

            int result = (a || b) ? 1 : 0;
            machine.Stack.PushInt(result);

            return true;
        }

        public override string ToString()
        {
            return "|";
        }
    }
}
