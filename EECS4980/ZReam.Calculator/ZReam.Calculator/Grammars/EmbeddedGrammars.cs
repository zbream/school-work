using System.IO;
using System.Reflection;

namespace ZReam.Calculator.Grammars
{
    public static class EmbeddedGrammars
    {
        private const string MATH_RAW = "ZReam.Calculator.Grammars.Math.grxml";
        private const string MATH_COMPILED = "ZReam.Calculator.Grammars.Math.cfg";
        private const string COMMANDS_RAW = "ZReam.Calculator.Grammars.Commands.grxml";
        private const string COMMANDS_COMPILED = "ZReam.Calculator.Grammars.Commands.cfg";

        private static Stream GetEmbeddedResourceStream(string resourceName)
        {
            return Assembly.GetExecutingAssembly().GetManifestResourceStream(resourceName);
        }

        public static Stream MathRaw
        {
            get
            {
                return GetEmbeddedResourceStream(MATH_RAW);
            }
        }

        public static Stream MathCompiled
        {
            get
            {
                return GetEmbeddedResourceStream(MATH_COMPILED);
            }
        }

        public static Stream CommandsRaw
        {
            get
            {
                return GetEmbeddedResourceStream(COMMANDS_RAW);
            }
        }

        public static Stream CommandsCompiled
        {
            get
            {
                return GetEmbeddedResourceStream(COMMANDS_COMPILED);
            }
        }
    }
}
