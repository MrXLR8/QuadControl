using Sockets.Plugin;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking.Sockets;

namespace ArduinoProject.Shared
{
   public static class SocketConnection
    {

        private static  String address = "192.168.1.123";
        private static  String port = "49123";
        private static Task connectTask;
        private static StreamSocket _socket;
        private static TcpSocketClient client;
        public static void connect()
        {


            client = new TcpSocketClient();
            connectTask= client.ConnectAsync(address, port);
            

            // we're connected!


        }


        public static async void write(String data)
        {
            
            if(connectTask==null)  connect(); 
            await connectTask;
                data += Environment.NewLine;
                 byte[] bytes = Encoding.ASCII.GetBytes(data);

                // write to the 'WriteStream' property of the socket client to send data
                client.WriteStream.Write(bytes,0,bytes.Length);
                await client.WriteStream.FlushAsync();

                // wait a little before sending the next bit of data
                await Task.Delay(TimeSpan.FromMilliseconds(500));
            
        }

        public static async void disconnect()
        {
            await client.DisconnectAsync();
        }
    }
}
