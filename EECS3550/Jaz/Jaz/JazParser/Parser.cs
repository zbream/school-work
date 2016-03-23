// 3550 Programming Asignment ZackReam JordanKlamut

using System.IO;
using System.Linq;
using System.Text;
using Jaz.JazExecutor;

namespace Jaz.JazParser
{
    class Parser
    {
        public static void ParseProgram(Executor executor, StreamReader stream)
        {
            string line, lval, rval;
            withinBlockComment = false;

            while (!stream.EndOfStream)
            {
                line = stream.ReadLine();
                handleLine(line, out lval, out rval);

                if (!string.IsNullOrEmpty(lval))
                {
                    executor.ParseAndAddAction(lval, rval);
                }
            }
        }

        private static void handleLine(string line, out string lval, out string rval)
        {
            // handle comments
            line = trimComments(line);

            // trim leading and trailing spaces,tabs
            line = line.Trim(' ', '\t');

            // split into l and r
            int sep = line.IndexOf(' ');
            if (sep == -1)
            {
                lval = line;
                rval = null;
            }
            else
            {
                lval = line.Substring(0, sep);
                rval = line.Substring(sep + 1);
            }
        }

        private static bool withinBlockComment = false;

        private static string trimComments(string line)
        {
            // Slide down the line with a head width of 2.
            // Handle comment state based on the current [0] and next [1] char.
            // If we are NOT part of a comment or comment-declaration pair, add current [0] to output.

            StringBuilder output = new StringBuilder();
            bool withinLineComment = false;
            bool ignoreNextChar = false;

            // the head needs room to maneuver
            line = line + '\0';

            // at the start of the loop, the head will be at
            // the start of 'line' as given as a parameter
            char[] head = { '\0', line[0] };

            for (int i = 1; i < line.Length; i++)
            {
                head[0] = head[1];
                head[1] = line[i];

                // if head[0] was part of a comment-declaration pair, ignore
                if (ignoreNextChar)
                {
                    ignoreNextChar = false;
                    continue;
                }

                // if in a block comment, nothing can happen unless it closes
                if (withinBlockComment)
                {
                    // check for ending block comment
                    if (head.SequenceEqual("*/"))
                    {
                        withinBlockComment = false;
                        ignoreNextChar = true;
                    }
                    continue;
                }

                // if in a line comment, nothing can happen
                if (withinLineComment)
                {
                    continue;
                }

                // check for beginning line comment 
                if (head.SequenceEqual("//"))
                {
                    withinLineComment = true;
                    ignoreNextChar = true;
                    continue;
                }

                // check for beginning block comment
                if (head.SequenceEqual("/*"))
                {
                    withinBlockComment = true;
                    ignoreNextChar = true;
                    continue;
                }

                // if we made it this far, this is a legitimate character
                output.Append(head[0]);
            }

            return output.ToString();
        }
    }
}
