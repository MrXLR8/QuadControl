using System;
using System.Collections.Generic;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace ArduinoProject
{
    
	public partial class App : Application
	{
        public IList<Page> PageList;
		public App ()
		{
			InitializeComponent();

            //MainPage = new MainPage();
            MainPage = new TabbedPage1();
            
        }

		protected override void OnStart ()
		{
			// Handle when your app starts
		}

		protected override void OnSleep ()
		{
			// Handle when your app sleeps
		}

		protected override void OnResume ()
		{
			// Handle when your app resumes
		}
	}
}
