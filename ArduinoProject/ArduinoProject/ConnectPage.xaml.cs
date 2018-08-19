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
            SocketConnection.onConnect = new boolDeleagate(onConnected);
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
            SocketConnection.disconnect();
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

        }
    }
}