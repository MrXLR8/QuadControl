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
       static FileImageSource IdleImage =new FileImageSource().File = "arrow_idle.png";
       static FileImageSource PressedImage = new FileImageSource().File = "arrow_pressed.png";
        public ControlPage ()
		{
			InitializeComponent ();
        //    up.Image = new FileImageSource().File = "arrow_idle.png";
          //  down.Source = ImageSource.FromFile("arrow_idle.png");
            //rollImage.Source = ImageSource.FromFile("roll.png");
            //pitchImage.Source = ImageSource.FromFile("pitch.png");
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

        private void Control_Pressed(object sender, EventArgs e)
        {
            Button target = (Button)sender;
            target.Image = PressedImage;
            motor1.Value = 0;
        }

        private void Control_Released(object sender, EventArgs e)
        {
            Button target = (Button)sender;
            target.Image =IdleImage;
            motor1.Value = 100;
        }
    }


}