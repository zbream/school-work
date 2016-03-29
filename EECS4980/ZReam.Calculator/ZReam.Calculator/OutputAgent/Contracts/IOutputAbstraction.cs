using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ZReam.Calculator.Math;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputAbstraction
    {
        AST CurrentOutput { get; set; }

        bool IsSpeechEnabled { get; set; }
    }
}
