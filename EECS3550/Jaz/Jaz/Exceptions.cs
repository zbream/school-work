// 3550 Programming Asignment ZackReam JordanKlamut

using System;

namespace Jaz
{
    [Serializable]
    public class ExecuteException : Exception
    {
        public ExecuteException() { }
        public ExecuteException(string message) : base(message) { }
        public ExecuteException(string message, Exception inner) : base(message, inner) { }
        protected ExecuteException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context) : base(info, context)
        { }
    }

    [Serializable]
    public class ParseException : Exception
    {
        public ParseException() { }
        public ParseException(string message) : base(message) { }
        public ParseException(string message, Exception inner) : base(message, inner) { }
        protected ParseException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context) : base(info, context)
        { }
    }
}
