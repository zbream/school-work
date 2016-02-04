using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jaz.JazMachine
{
    class MemoryManager
    {
        /*
        A subroutine starts with a unique scope of memory.
        Use [BEGIN, CALL, RETURN, END] sequence to pass variables.

        BEGIN/END enter/exit a parameter-sharing mode (split reading/writing between different scopes).
        CALL/RETURN enter/exit a subroutine mode.

        Read() and Write() come from different scopes depending on the current mode.

        Let's call the caller scope: parent
        Let's call the callee scope: child

        read parent, write parent (parent mode)
        BEGIN
        read parent, write child (parameter-passing mode)
        CALL
        read child, write child (subroutine mode)
        RETURN
        read child, write parent (parameter-retrieving mode)
        END
        read parent, write parent (parent mode)

        Within the CALL and RETURN commands (the subroutine), you can start 
        another [BEGIN, CALL, RETURN, END] sequence with a new scope.
        */

        public MemoryManager()
        {
            scopes = new List<Dictionary<string, int>>();

            // initialize first memory location (main scope)
            scopes.Add(new Dictionary<string, int>());
            scopeRead = 0;
            scopeWrite = 0;
        }

        private List<Dictionary<string, int>> scopes;
        private int scopeRead, scopeWrite;

        public void Write(string key, int value)
        {
            // if calling sequence is followed properly, this should never fail
            Dictionary<string, int> scope = scopes[scopeWrite];

            scope[key] = value;
        }

        public int Read(string key)
        {
            // if calling sequence is followed properly, this should never fail
            Dictionary<string, int> scope = scopes[scopeRead];

            // defaults to 0 if not found
            int value;
            scope.TryGetValue(key, out value);

            return value;
        }

        // BEGIN
        public void EnterParameterPassing()
        {
            scopeWrite++;
            scopes.Add(new Dictionary<string, int>());
        }

        // CALL
        public void EnterSubroutine()
        {
            scopeRead++;
        }

        // RETURN
        public void ExitSubroutine()
        {
            scopeWrite--;
        }

        // END
        public void ExitParameterPassing()
        {
            scopeRead--;
            scopes.RemoveAt(scopes.Count - 1);
        }
    }
}
