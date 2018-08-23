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
        }
	}
}