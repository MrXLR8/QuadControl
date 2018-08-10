using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;

namespace ArduinoProject.Shared
{
   public static class SocketConnection
    {

        private static IPAddress address = IPAddress.Parse("192.168.1.123");
        private static  int port = 49123;
        private static Task connectTask;


        private static NetworkStream ClientStream;
        private static NetworkStream ReciverStream;
       
        private static TcpClient ClientSocket;
        private static TcpListener ReciverSocket;
        public static void connect()
        {
            ClientSocket = new TcpClient();
            
            connectTask= ClientSocket.ConnectAsync(address, port);
            

            // we're connected!


        }


        public static async void write(String data)
        {
            
            if(connectTask==null)  connect(); 
            await connectTask;

            ClientStream = ClientSocket.GetStream();

                data += Environment.NewLine;
                 byte[] bytes = Encoding.ASCII.GetBytes(data);

                // write to the 'WriteStream' property of the socket client to send data

               ClientStream.Write(bytes,0,bytes.Length);
            await ClientStream.FlushAsync();

                // wait a little before sending the next bit of data
                await Task.Delay(TimeSpan.FromMilliseconds(500));
            
        }

        public static async void disconnect()
        {
            ClientSocket.Close();
        }
    }
}
