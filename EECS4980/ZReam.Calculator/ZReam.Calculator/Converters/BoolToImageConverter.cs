using System;
using System.Globalization;
using System.Windows.Data;

namespace ZReam.Calculator.Converters
{
    public class BoolToImageConverter : IValueConverter
    {
        public string TrueImage { get; set; }
        public string FalseImage { get; set; }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return ((bool)value ? TrueImage : FalseImage);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
