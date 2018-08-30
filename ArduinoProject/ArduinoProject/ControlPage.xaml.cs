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

            motor1.Value=  Shared.Method.map(pitch,-180,180,0,100);
            motor4.Value = Shared.Method.map(roll, -180, 180, 0, 100);
        }
        private void VerticalSlider_onSliderChanged(VerticalSlider sender)
        {

            //FormAction.print($"{sender.CompName}: {sender.Value}");
        }

        private void Button_Clicked(object sender, EventArgs e)
        {
    
        }
    }


}