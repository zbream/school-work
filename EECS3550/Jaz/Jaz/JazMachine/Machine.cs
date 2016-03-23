// 3550 Programming Asignment ZackReam JordanKlamut

using System.Collections.Generic;

namespace Jaz.JazMachine
{
    class Machine
    {
        public Machine()
        {
            this.Stack = new StackManager();
            this.Memory = new MemoryManager();
            this.ReturnStack = new Stack<int>();
            this.Pointer = 0;
        }

        public StackManager Stack { get; private set; }

        public MemoryManager Memory { get; private set; }

        public Stack<int> ReturnStack { get; private set; }

        public int Pointer;
    }
}
