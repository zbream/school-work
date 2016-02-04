using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.SubprogramControl
{
    class EAbegin : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            machine.Memory.EnterParameterPassing();

            return true;
        }

        public override string ToString()
        {
            return "begin";
        }
    }

    class EAend : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            machine.Memory.ExitParameterPassing();

            return true;
        }

        public override string ToString()
        {
            return "end";
        }
    }

    class EAreturn : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            if (machine.ReturnStack.Count > 0)
            {
                machine.Memory.ExitSubroutine();

                machine.Pointer = machine.ReturnStack.Pop();
            }
            else
            {
                throw new ExecuteException("Command \"return\" called not from within a subroutine.");
            }

            return true;
        }

        public override string ToString()
        {
            return "return";
        }
    }

    class EAcall : IExecutorAction
    {
        public EAcall(string rval, IReadOnlyDictionary<string, int> labels)
        {
            this.destLabel = rval;
            this.labels = labels;
        }

        private string destLabel;
        private IReadOnlyDictionary<string, int> labels;

        public bool Perform(Machine machine)
        {
            int destPointer;
            if (!labels.TryGetValue(destLabel, out destPointer))
            {
                throw new ExecuteException("Label not found: " + destLabel);
            }

            machine.Memory.EnterSubroutine();

            machine.ReturnStack.Push(machine.Pointer);
            machine.Pointer = labels[destLabel];

            return false;
        }

        public override string ToString()
        {
            return "call " + destLabel;
        }
    }
}
