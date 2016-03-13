using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction.ControlFlow
{
    class EAgoto : IExecutorAction
    {
        public EAgoto(string rval, IReadOnlyDictionary<string, int> labels)
        {
            this.destLabel = rval;
            this.labels = labels;
        }

        protected string destLabel;
        private IReadOnlyDictionary<string, int> labels;

        public virtual bool Perform(Machine machine)
        {
            int destPointer;
            if (!labels.TryGetValue(destLabel, out destPointer))
            {
                throw new ExecuteException(string.Format("Label not found, \"{0}\".", destLabel));
            }

            machine.Pointer = destPointer;

            return false;
        }

        public override string ToString()
        {
            return "goto " + destLabel;
        }
    }

    class EAgofalse : EAgoto
    {
        public EAgofalse(string rval, IReadOnlyDictionary<string, int> labels) : base(rval, labels) { }

        public override bool Perform(Machine machine)
        {
            int top = machine.Stack.PopInt();
            if (top == 0)
            {
                return base.Perform(machine);
            }

            return true;
        }

        public override string ToString()
        {
            return "gofalse " + destLabel;
        }
    }

    class EAgotrue : EAgoto
    {
        public EAgotrue(string rval, IReadOnlyDictionary<string, int> labels) : base(rval, labels) { }

        public override bool Perform(Machine machine)
        {
            int top = machine.Stack.PopInt();
            if (top != 0)
            {
                return base.Perform(machine);
            }

            return true;
        }

        public override string ToString()
        {
            return "gotrue " + destLabel;
        }
    }

    class EAhalt : IExecutorAction
    {
        public bool Perform(Machine machine)
        {
            machine.Pointer = -1;

            return false;
        }

        public override string ToString()
        {
            return "halt";
        }
    }
}