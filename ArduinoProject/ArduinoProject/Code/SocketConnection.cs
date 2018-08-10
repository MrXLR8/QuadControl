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

        private static IPAddress address = IPAddress.Parse("192.168.1.124");
        private static  int port = 49123;
        private static Task connectTask;


        private static NetworkStream ClientStream;
        private static NetworkStream ReciverStream;
       
        private static TcpClient ClientSocket=new TcpClient();
       // private static TcpListener ReciverSocket = new TcpListener(port);
        public static async Task<bool> connect()
        {
            try
            {
                await ClientSocket.ConnectAsync(address, port);
                ClientStream = ClientSocket.GetStream();
                
                return true;
            }
            catch(Exception e)
            {
                Code.FormAction.print("Failed to connect to: " + address + ":" + port);
                return false;
            }

            // we're connected!


        }


        public static async void write(String data)
        {
          
            if(!ClientSocket.Connected)
            {
               if(!await connect())
                {
                    return;
                }
            }

                data += Environment.NewLine;
                 byte[] bytes = Encoding.ASCII.GetBytes(data);

                // write to the 'WriteStream' property of the socket client to send data

               ClientStream.Write(bytes,0,bytes.Length);
            await ClientStream.FlushAsync();

                // wait a little before sending the next bit of data
                await Task.Delay(TimeSpan.FromMilliseconds(500));
            
        }

        public static async void listen()
        {

            if (!ClientSocket.Connected)
            {
                if (!await connect())
                {
                    return;
                }
            }

            String decode;
            String result = "";
            byte[] buffer = new byte[1];
            if (ClientSocket.Connected) Code.FormAction.print("Listener stated");
            while (ClientSocket.Connected)
            {
                buffer[0]= (byte)ClientStream.ReadByte();
                decode= Encoding.ASCII.GetString(buffer);
                if (buffer[0]==13)
                {
                    Code.FormAction.print("Recived: " + result);
                    result = "";
                }
                else
                {
                    if(buffer[0]!=10)
                    result += decode;
                }
      
            }
            
        }



        public static async void disconnect()
        {
            ClientSocket.Close();
        }
    }
}
