using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace ArduinoProject.Code
{

    public static class FormAction
    {
        public static MainPage Form;
        public static int inputCounter;
        public static int outputCounter;

        public static void printRecivedData(string text)
        {
            Device.BeginInvokeOnMainThread(() =>
            {
                if (inputCounter > 20)
                {
                    Form.InputData.Text = "";
                    inputCounter = 0;
                }
                inputCounter++;
                Form.InputData.Text += Environment.NewLine + " " + text;
          
        
                Form.InputScrollText.ScrollToAsync(Form.InputData, Xamarin.Forms.ScrollToPosition.End, true);
            });
        }

        public static void printSentData(string text)
        {
            Device.BeginInvokeOnMainThread(() =>
            {
                if (outputCounter > 20)
                {
                    Form.OutputData.Text = "";
                    outputCounter = 0;
                }
                outputCounter++;
                Form.OutputData.Text +=  "\n " + text;
               Form.OutputScrollText.ScrollToAsync(Form.OutputData, Xamarin.Forms.ScrollToPosition.End, true);
            });
        }

    }
}

