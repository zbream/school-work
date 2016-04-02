using System.IO;
using System.Reflection;

namespace ZReam.Calculator.Grammars
{
    public static class EmbeddedGrammars
    {
        private const string MATH_RAW = "ZReam.Calculator.Grammars.Math.grxml";
        private const string MATH_COMPILED = "ZReam.Calculator.Grammars.Math.cfg";

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

    }
}
