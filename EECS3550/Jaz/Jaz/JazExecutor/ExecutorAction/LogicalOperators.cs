using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.LogicalOperators
{
    class EAand : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            bool a = ((int)machine.Stack.Pop()) != 0;
            bool b = ((int)machine.Stack.Pop()) != 0;

            int result = (a && b) ? 1 : 0;
            machine.Stack.Push(result);

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
            bool a = ((int)machine.Stack.Pop()) != 0;

            int result = (!a) ? 1 : 0;
            machine.Stack.Push(result);

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
            bool a = ((int)machine.Stack.Pop()) != 0;
            bool b = ((int)machine.Stack.Pop()) != 0;

            int result = (a || b) ? 1 : 0;
            machine.Stack.Push(result);

            return true;
        }

        public override string ToString()
        {
            return "|";
        }
    }
}
