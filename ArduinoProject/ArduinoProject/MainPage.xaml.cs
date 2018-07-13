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
               Bluetooth.Send(1);

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
    }
}
