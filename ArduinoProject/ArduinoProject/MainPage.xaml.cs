using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using ArduinoProject.Shared;

namespace ArduinoProject
{
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
               Bluetooth.SendAsync(1);

            }
            else if(Button==yellBTN)
            {
                Bluetooth.SendAsync(2);
            }
            else if(Button==redTN)
            {

                Bluetooth.SendAsync(3);
            }
            else if(Button==offBTN)
            {

                Bluetooth.SendAsync(0);
                
            }
        }

        private void Power_Click(object sender, EventArgs e)
        {
            print("Power click");
            var Button = sender as Button;
            if(Button==PowerDown)
            {
                print("PWR "+power.ToString());
                if ((power-change)>=0)
                {
                    power -= change;
                }

            }
            if(Button==PowerUp)
            {
                print("PWR "+power.ToString());
                if ((power+change)<=9)
                {
                    power += change;
                }

            }
            PowerText.Text = power.ToString();
            Bluetooth.SendAsync(power);
        }
    }
}
