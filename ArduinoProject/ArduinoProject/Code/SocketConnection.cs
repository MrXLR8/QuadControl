using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using ArduinoProject.Code;
using System.Threading;

namespace ArduinoProject.Shared
{
   public static class SocketConnection
    {

        private static IPAddress address;
        private static int port;
        public static boolDelegate onConnect;
        public static voidDelegate onDisconnect;
        public static stringDelegate parseInfo;

        private static NetworkStream ClientStream;

        private static TcpClient ClientSocket;
       // private static TcpListener ReciverSocket = new TcpListener(port);
        public static async Task<bool> connect(string _ip,int _port)
        {
           
            try
            {
                ClientSocket = new TcpClient(); 

                address = IPAddress.Parse(_ip);
                port = _port;

                await ClientSocket.ConnectAsync(address, port);
                ClientStream = ClientSocket.GetStream();
           
                new Task(new Action(listen)).Start();

              

                onConnect?.Invoke(true);
                new Order("[WP]1").Execute(); //PING
                return true;
            }
            catch(Exception e)
            {
                Code.FormAction.printSentData("Failed to connect to: " + address + ":" + port);
                onConnect?.Invoke(false);
                return false;
            }

            // we're connected!


        }


        public static async void write(String data)
        {
            if (ClientSocket == null) return;
            if(!ClientSocket.Connected) return;
           

                data += Environment.NewLine;
                 byte[] bytes = Encoding.ASCII.GetBytes(data);

   

               ClientStream.Write(bytes,0,bytes.Length);
            Code.FormAction.printSentData(data);
            await ClientStream.FlushAsync();


                await Task.Delay(TimeSpan.FromMilliseconds(500));
            
        }

        public static async void listen()
        {
            Semaphore execute = new Semaphore(1, 1);


            if (!ClientSocket.Connected)
            {
                    return;
            }
            bool contniute = false;
            String decode;
            String result = "";
            byte[] buffer = new byte[1];
            if (ClientSocket.Connected) Code.FormAction.printSentData("Listener stated");
            while (ClientSocket.Connected)
            {
                try
                {
                    buffer[0] = (byte)ClientStream.ReadByte();
                    
                }
                catch (Exception e) { return; }
                decode= Encoding.ASCII.GetString(buffer);
                if (buffer[0]==13| buffer[0] == 10)
                {
                    if (result != "")
                    {
                        Xamarin.Forms.Device.BeginInvokeOnMainThread(() =>
                        {

                            if (result.Length>3)
                            {
                                contniute = false;
                              //  Code.FormAction.print(">>>: " + result);
                                if (result[0] == '['&&result[3]==']')
                                {
                                    Code.FormAction.printRecivedData(result);
                                    new Order(result).Execute();
                                    
                                }
                                contniute = true;
                            }
                        });
                       while(!contniute) { Thread.Sleep(10); }
                        result = "";
                        contniute = false;

                    }
                }
                else
                {
                    if(buffer[0]!='\0')
                    result += decode;
                }
      
            }
            
        }



        public static async void disconnect()
        {
            ClientSocket.Close();
           
            onDisconnect?.Invoke();
        }
    }
}
