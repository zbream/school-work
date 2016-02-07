using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.StackManipulation
{
    class EApush : IExecutorAction
    {
        public EApush(string rval)
        {
            if (!int.TryParse(rval, out value))
            {
                throw new ParseException("Command \"push\" must be followed by a number.");
            }
        }

        private int value;

        public bool Perform(Machine machine)
        {
            machine.Stack.PushInt(value);

            return true;
        }

        public override string ToString()
        {
            return "push " + value;
        }
    }

    class EArvalue : IExecutorAction
    {
        public EArvalue(string rval)
        {
            this.variable = rval;
        }

        private string variable;

        public bool Perform(Machine machine)
        {
            int value = machine.Memory.Read(variable);
            machine.Stack.PushInt(value);

            return true;
        }

        public override string ToString()
        {
            return "rvalue " + variable;
        }
    }

    class EAlvalue : IExecutorAction
    {
        public EAlvalue(string rval)
        {
            this.value = rval;
        }

        private string value;

        public bool Perform(Machine machine)
        {
            machine.Stack.PushString(value);

            return true;
        }

        public override string ToString()
        {
            return "lvalue " + value;
        }
    }

    class EApop : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            machine.Stack.PopString();

            return true;
        }

        public override string ToString()
        {
            return "pop";
        }
    }

    class EAassign : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            int value = machine.Stack.PopInt();
            string variable = (string)machine.Stack.PopString();

            machine.Memory.Write(variable, value);

            return true;
        }

        public override string ToString()
        {
            return ":=";
        }
    }

    class EAcopy : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            machine.Stack.CopyTop();

            return true;
        }

        public override string ToString()
        {
            return "copy";
        }
    }
}
