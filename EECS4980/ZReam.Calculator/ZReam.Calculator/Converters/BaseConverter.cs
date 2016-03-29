using System;
using System.Windows.Markup;

namespace ZReam.Calculator.Converters
{
    public class BaseConverter : MarkupExtension
    {
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return this;
        }
    }
}
