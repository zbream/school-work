using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazExecutor.ExecutorAction;
using Jaz.JazMachine;

namespace Jaz.JazExecutor
{
    class Executor
    {
        public Executor()
        {
            actions = new List<IExecutorAction>();
            labels = new Dictionary<string, int>();
        }

        private List<IExecutorAction> actions;
        private Dictionary<string, int> labels;

        public void Execute(Machine machine)
        {
            // something's wrong if we exceed this pointer
            int pointerMax = actions.Count - 1;

            // with no actions to perform, Pointer would start outside pointerMax
            if (pointerMax < 0)
            {
                return;
            }

            // begin execution
            while (machine.Pointer >= 0)
            {
                // assert that pointer remains within code
                if (machine.Pointer > pointerMax)
                {
                    throw new ExecuteException("Execution has left the written code. Are you missing a halt or return?");
                }

                // perform, and move pointer if necessary
                IExecutorAction action = actions[machine.Pointer];
                bool advancePointer = action.Perform(machine);
                if (advancePointer)
                {
                    machine.Pointer++;
                }
            }
        }

        public void ParseAndAddAction(string lval, string rval)
        {
            IExecutorAction action = parseAction(lval, rval);

            // some commands, like "label", do not have an associated action
            if (action != null)
            {
                actions.Add(action);
            }
        }

        private IExecutorAction parseAction(string lval, string rval)
        {
            switch (lval.ToLower())
            {
                // Stack Manipulation
                case "push":
                    return new ExecutorAction.StackManipulation.EApush(rval);
                case "rvalue":
                    return new ExecutorAction.StackManipulation.EArvalue(rval);
                case "lvalue":
                    return new ExecutorAction.StackManipulation.EAlvalue(rval);
                case "pop":
                    return new ExecutorAction.StackManipulation.EApop();
                case ":=":
                    return new ExecutorAction.StackManipulation.EAassign();
                case "copy":
                    return new ExecutorAction.StackManipulation.EAcopy();

                // Control Flow
                case "label":
                    // mark the position of the next command
                    labels.Add(rval, actions.Count);
                    return null;
                case "goto":
                    return new ExecutorAction.ControlFlow.EAgoto(rval, labels);
                case "gofalse":
                    return new ExecutorAction.ControlFlow.EAgofalse(rval, labels);
                case "gotrue":
                    return new ExecutorAction.ControlFlow.EAgotrue(rval, labels);
                case "halt":
                    return new ExecutorAction.ControlFlow.EAhalt();

                // Arithmetic Operators
                case "+":
                    return new ExecutorAction.ArithmeticOperators.EAadd();
                case "-":
                    return new ExecutorAction.ArithmeticOperators.EAsub();
                case "*":
                    return new ExecutorAction.ArithmeticOperators.EAmul();
                case "/":
                    return new ExecutorAction.ArithmeticOperators.EAdiv();
                case "div":
                    return new ExecutorAction.ArithmeticOperators.EAmod();

                // Logical Operators
                case "&":
                    return new ExecutorAction.LogicalOperators.EAand();
                case "!":
                    return new ExecutorAction.LogicalOperators.EAnot();
                case "|":
                    return new ExecutorAction.LogicalOperators.EAor();

                // Relational Operators
                case "<>":
                    return new ExecutorAction.RelationalOperators.EAne();
                case "<=":
                    return new ExecutorAction.RelationalOperators.EAle();
                case ">=":
                    return new ExecutorAction.RelationalOperators.EAge();
                case "<":
                    return new ExecutorAction.RelationalOperators.EAlt();
                case ">":
                    return new ExecutorAction.RelationalOperators.EAgt();
                case "=":
                    return new ExecutorAction.RelationalOperators.EAeq();

                // Output
                case "print":
                    return new ExecutorAction.Output.EAprint();
                case "show":
                    return new ExecutorAction.Output.EAshow(rval);

                // Subprogram Control
                case "begin":
                    return new ExecutorAction.SubprogramControl.EAbegin();
                case "end":
                    return new ExecutorAction.SubprogramControl.EAend();
                case "return":
                    return new ExecutorAction.SubprogramControl.EAreturn();
                case "call":
                    return new ExecutorAction.SubprogramControl.EAcall(rval, labels);
                default:
                    throw new ParseException("Unfamiliar command: \"" + lval + "\"");
            }
        }
    }
}
