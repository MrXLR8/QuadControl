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
        private string lastSent = String.Empty;

        public MainPage()
		{

			InitializeComponent();
            ArduinoProject.Code.FormAction.Form = this;
            
            

		}

        public void print(string text)
        {
            // TextField.Text += Environment.NewLine+" "+ text;
        }

        private void Button_Clicked(object sender, EventArgs e)
        {
            
            var Button = sender as Button;

            if (Button == lastBTN)
            {

                DataField.Text = lastSent;

            }
            else if (Button == maBTN)
            {
                Variable.MotorAllow = !Variable.MotorAllow;
                String result = Variable.MotorAllow ? "1" : "0";
                SocketConnection.write("[MA]"+result);
            }
            else if(Button== clearBTN)
            {
                FormAction.inputCounter = 0;
                FormAction.outputCounter = 0;
                InputData.Text = String.Empty;
                OutputData.Text= String.Empty;
            }

        }


        private void TextField_Focused(object sender, FocusEventArgs e)
        {
            ((Editor)sender).Unfocus();
        }

        private void DataField_Completed(object sender, EventArgs e)
        {
            String text = DataField.Text;
            SocketConnection.write(text);
            lastSent = text;
            DataField.Text = "";
        }
    }
}
