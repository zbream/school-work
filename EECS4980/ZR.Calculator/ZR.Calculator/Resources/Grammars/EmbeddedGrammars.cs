using System.IO;
using System.Reflection;

namespace ZR.Calculator.Resources.Grammars
{
    public static class EmbeddedGrammars
    {
        private const string MATH_RAW = "Math.grxml";
        private const string MATH_COMPILED = "Math.cfg";
        private const string COMMANDS_RAW = "Commands.grxml";
        private const string COMMANDS_COMPILED = "Commands.cfg";

        private static Stream GetEmbeddedResourceStream(string resourceName)
        {
            string fullName = typeof(EmbeddedGrammars).Namespace + "." + resourceName;
            return Assembly.GetExecutingAssembly().GetManifestResourceStream(fullName);
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
