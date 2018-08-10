using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace ArduinoProject.Code
{

    public static class FormAction
    {
        public static MainPage Form;

        public static void print(string text)
        {
            Device.BeginInvokeOnMainThread(() =>
            {

                Form.TextField.Text += Environment.NewLine + " " + text;
                Form.ScrollText.ScrollToAsync(Form.TextField, Xamarin.Forms.ScrollToPosition.End, true);
            });
        }
    }
}

