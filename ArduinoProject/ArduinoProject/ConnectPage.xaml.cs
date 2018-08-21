using ArduinoProject.Code;
using ArduinoProject.Shared;
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
	public partial class ConnectPage : ContentPage
	{
		public ConnectPage ()
		{

            InitializeComponent();
            SocketConnection.onConnect = new boolDelegate(onConnected);
            Ping.pingFinished = Ping_Recived;
        }

        private void ConnectionButton_Clicked(object sender, EventArgs e)
        {
            SocketConnection.connect(ipEntry.Text,Convert.ToInt32(portEntry.Text));

            ConnectionStatus.Text = "Connecting...";
            ConnectionStatus.TextColor = Color.Gray;
            ConnectionButton.IsEnabled = false;
        }

        private void DisconnectButton_Clicked(object sender, EventArgs e)
        {
            new Order("[WP]2").Execute();
        }


        private void onConnected(bool status)
        {
            if (status)
            {
                ConnectionStatus.Text = "Connected";
                ConnectionStatus.TextColor = Color.Green;
            }
            else
            {
                ConnectionStatus.Text = "Failed";
                ConnectionStatus.TextColor = Color.Red;
            }
            ConnectionButton.IsEnabled = true;
        }

        private void PingButton_Clicked(object sender, EventArgs e)
        {
            PingMS.Text = "...";
            Order go = new Order("[WP]1");
            go.Execute();
            
        }

        private void Ping_Recived(int mills)
        {
            if (mills >= 1000)
            {
                PingMS.Text =  "Time out";
            }
            else
            {
                PingMS.Text = mills.ToString() + " ms";
            }
            
        }
    }
}