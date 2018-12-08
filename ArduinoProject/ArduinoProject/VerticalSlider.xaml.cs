using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace ArduinoProject
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class VerticalSlider : Grid
	{

        private string _name;
        private double _value;
        public string CompName
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }
       // public EventHandler<ValueChangedEventArgs> onSliderChanged;

        public delegate void sliderChange(VerticalSlider sld);
        public event sliderChange onSliderChanged;

        public double Value
        {
            get
            {
                return _value;
            }
            set
            {
                _value = value;
                FormSlider.Value = _value;
                FormLabel.Text = _value.ToString();

            }
        }

        


        public VerticalSlider ()
		{
			InitializeComponent ();
            FormSlider.ValueChanged += sliderChanged;
            FormSlider.ClassId = CompName;
            FormSlider.IsEnabled = false;
		}

        private void sliderChanged(object sender, ValueChangedEventArgs e)
        {
            Value = FormSlider.Value;
            colorSet((int)_value);
            onSliderChanged?.Invoke(this);
        }

        private void colorSet(int val)
        {
            int red = Shared.Method.map(val, Shared.Variable.middlePower, 100, 0, 255);
            int green= Shared.Method.map(Shared.Variable.middlePower - Math.Abs(Shared.Variable.middlePower - val)     , 0, Shared.Variable.middlePower, 0, 255);
            inGrid.BackgroundColor = Color.FromRgb(red, green, 0);
        }
	}
}