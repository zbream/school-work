// 3550 Programming Asignment ZackReam JordanKlamut

using System.Collections.Generic;

namespace Jaz.JazMachine
{
    class StackManager
    {
        public StackManager()
        {
            stack = new Stack<object>();
        }

        private Stack<object> stack;

        public void PushInt(int value)
        {
            stack.Push(value);
        }

        public void PushString(string value)
        {
            stack.Push(value);
        }

        public int PopInt()
        {
            return enforceInt(stack.Pop());
        }

        public string PopString()
        {
            return stack.Pop().ToString();
        }

        public int PeekInt()
        {
            return enforceInt(stack.Pop());
        }

        public string PeekString()
        {
            return stack.Peek().ToString();
        }

        public void CopyTop()
        {
            stack.Push(stack.Peek());
        }

        private int enforceInt(object value)
        {
            if (value.GetType() == typeof(int))
            {
                return (int)value;
            }
            else
            {
                throw new ExecuteException("Top of Stack is not an integer.");
            }
        }
    }
}
