using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ZReam.Calculator.Math;
using ZReam.Calculator.OutputAgent.Contracts;

namespace ZReam.Calculator.OutputAgent
{
    class OutputAbstraction : IOutputAbstraction
    {
        public AST CurrentOutput { get; set; }
    }
}
