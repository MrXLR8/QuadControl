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
            MotorData.motorFinished = updateMotorSliders;
        }


        void updateGyroFields(int pitch, int roll)
        {
            pitchLabel.Text = pitch.ToString();
            rollLabel.Text = (roll*-1).ToString();


        }

        void updateMotorSliders(int m1,int m2,int m3,int m4)
        {
            motor1.Value = m1;
            motor2.Value = m2;
            motor3.Value = m3;
            motor4.Value = m4;
        }


        private void Control_Pressed(object sender, EventArgs e)
        {
            Button target = (Button)sender;
            target.Image = PressedImage;
        }




        private void Control_Released(object sender, EventArgs e)
        {
            Button target = (Button)sender;
            target.Image =IdleImage;

            if(target==pullUP|target==pullDOWN)
            {
                PullButton_Released(target);
            }

        }

        private void PullButton_Released(Button sender)
        {

        }
    }


}