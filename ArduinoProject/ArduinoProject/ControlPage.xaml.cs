using ArduinoProject.Code;
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
	public partial class ControlPage : ContentPage
	{
		public ControlPage ()
		{
			InitializeComponent ();
            up.Source = ImageSource.FromFile("arrow_idle.png");
            down.Source = ImageSource.FromFile("arrow_idle.png");
            rollImage.Source = ImageSource.FromFile("roll.png");
            pitchImage.Source = ImageSource.FromFile("pitch.png");
            GyroData.gyroFinished = updateGyroFields;
        }


        void updateGyroFields(int pitch, int roll)
        {
            pitchLabel.Text = pitch.ToString();
            rollLabel.Text = roll.ToString();
        }
        private void VerticalSlider_onSliderChanged(VerticalSlider sender)
        {

            FormAction.print($"{sender.CompName}: {sender.Value}");
        }

        private void Button_Clicked(object sender, EventArgs e)
        {
            motor1.Value = 10;
        }
    }


}