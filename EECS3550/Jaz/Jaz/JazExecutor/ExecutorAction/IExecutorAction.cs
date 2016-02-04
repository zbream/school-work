using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Jaz.JazMachine;

namespace Jaz.JazExecutor.ExecutorAction
{
    interface IExecutorAction
    {
        bool Perform(Machine machine);
    }
}
