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


        const int angleChange = 10;


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

            switch (target.ClassId)
            {
                case "up":
                    Stablizing.AddRequest(Stablizing.Angle.Pitch, angleChange);
                    break;
                case "down":
                    Stablizing.AddRequest(Stablizing.Angle.Pitch, -angleChange);
                    break;
                case "left":
                    Stablizing.AddRequest(Stablizing.Angle.Roll, angleChange);
                    break;
                case "right":
                    Stablizing.AddRequest(Stablizing.Angle.Roll, -angleChange);
                    break;

            }

            sendControlData();
        }




        private void Control_Released(object sender, EventArgs e)
        {
            Button target = (Button)sender;
            target.Image =IdleImage;

            if(target==pullUP|target==pullDOWN)
            {
                PullButton_Released(target);
            }
            
            switch(target.ClassId)
            {
                case "up":
                    Stablizing.RemoveRequest(Stablizing.Angle.Pitch, angleChange);
                    break;
                case "down":
                    Stablizing.RemoveRequest(Stablizing.Angle.Pitch, -angleChange);
                    break;
                case "left":
                    Stablizing.RemoveRequest(Stablizing.Angle.Roll, angleChange);
                    break;
                case "right":
                    Stablizing.RemoveRequest(Stablizing.Angle.Roll, -angleChange);
                    break;

            }


            sendControlData();
        }

        private void PullButton_Released(Button sender)
        {
            switch(sender.ClassId)
            {
                case "pUP":
                    Stablizing.MotorPower += 1;
                    break;
                case "pDOWN":
                    Stablizing.MotorPower -= 1;
                    break;
            }
            push.Value = Stablizing.MotorPower;
            
        }

        private void sendControlData()
        {
            String StringOrder=Stablizing.Form().ToString();
            Shared.SocketConnection.write(StringOrder);
        }

    }


}