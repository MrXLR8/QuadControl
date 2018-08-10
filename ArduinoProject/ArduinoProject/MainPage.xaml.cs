using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using ArduinoProject.Shared;
using ArduinoProject.Code;

namespace ArduinoProject
{
    //TODO: кнопка ручного подлкючения
	public partial class MainPage : ContentPage
	{
        public static int power = 0;
        public const int change = 1;
		public MainPage()
		{

			InitializeComponent();
            ArduinoProject.Code.FormAction.Form = this;
            
            

		}

        public void print(string text)
        {
             TextField.Text += Environment.NewLine+" "+ text;
        }

        private void Button_Clicked(object sender, EventArgs e)
        {
            
            var Button = sender as Button;

            if (Button==grnBTN)
            {
                SocketConnection.write("asd");

            }
            else if(Button==yellBTN)
            {
                Bluetooth.Send(2);
            }
            else if(Button==redTN)
            {

                Bluetooth.Send(3);
            }
            else if(Button==offBTN)
            {

                Bluetooth.Send(0);
                
            }
        }

        private void Power_Click(object sender, EventArgs e)
        {
            print("Power click");
            var Button = sender as Button;
            double calc;
            if(Button==PowerDown)
            {
                calc = power - change;
                if (calc >= 0)
                {
                    power -= change;
                }

            }
            if(Button==PowerUp)
            {

                calc = power + change;
                if (calc<=10)
                {
                    power += change;
                }

            }

            double progress = (double)power / 10;
            ProgressBarPower.Progress = progress;

            Bluetooth.Send(power * 25);
           
        }

        private void TextField_Focused(object sender, FocusEventArgs e)
        {
            ((Editor)sender).Unfocus();
        }

        private void DataField_Completed(object sender, EventArgs e)
        {
            String text = DataField.Text;
            SocketConnection.write(text);
            DataField.Text = "";
        }
    }
}
