using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jaz.JazMachine
{
    class Machine
    {
        public Machine()
        {
            this.Stack = new Stack<object>();
            this.Memory = new MemoryManager();
            this.ReturnStack = new Stack<int>();
            this.Pointer = 0;
        }

        public Stack<object> Stack { get; private set; }

        public MemoryManager Memory { get; private set; }

        public Stack<int> ReturnStack { get; private set; }

        public int Pointer;
    }
}
