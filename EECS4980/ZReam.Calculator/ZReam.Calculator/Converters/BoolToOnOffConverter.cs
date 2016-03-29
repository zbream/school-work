using System;
using System.Globalization;
using System.Windows.Data;

namespace ZReam.Calculator.Converters
{
    [ValueConversion(typeof(bool), typeof(string))]
    public class BoolToOnOffConverter : BaseConverter, IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return ((bool)value ? "ON" : "OFF");
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
