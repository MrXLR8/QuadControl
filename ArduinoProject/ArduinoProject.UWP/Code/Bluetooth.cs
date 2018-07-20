using ArduinoProject.Code;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Rfcomm;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Networking.Connectivity;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;

namespace ArduinoProject.Shared
{
    public static partial class Bluetooth
    {
         public static SerialPort port;


        /*
                      var serviceInfoCollection = await DeviceInformation.FindAllAsync(RfcommDeviceService.GetDeviceSelector(RfcommServiceId.SerialPort), new string[] { "System.Devices.AepService.AepId" });

            foreach (var serviceInfo in serviceInfoCollection)
            {
                var deviceInfo = await DeviceInformation.CreateFromIdAsync((string)serviceInfo.Properties["System.Devices.AepService.AepId"]);

                System.Diagnostics.Debug.WriteLine($"Device name is: '{deviceInfo.Name}' and Id is: '{deviceInfo.Id}'");

                if(deviceInfo.Name=="HC-05") { Target = deviceInfo; }
            }
            */

        private static void Start()
        {

           port = new SerialPort("COM4", 9600, Parity.None, 8, StopBits.One);

            port.ReadTimeout = 250;
            port.WriteTimeout = 250;



                port.Open();






        }

        public static void  ConnectDevice()
        {
        }

        public static void Send(string str)
        {
            if(port==null) { Start(); }


            FormAction.print("Отправляю строку:");
            FormAction.print("> " + str);
            if (port.IsOpen)
            {

                byte[] byteArray = Encoding.UTF8.GetBytes(str);
                port.Write(byteArray, 0, byteArray.Length);

            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
            }

        }

        public static  void Send(int number)
        {
            string str = number.ToString();

            if (port == null) { Start(); }


            FormAction.print("Отправляю строку:");
            FormAction.print("> " + str);
            if (port.IsOpen)
            {

                byte[] byteArray = Encoding.UTF8.GetBytes(str);
                port.Write(byteArray, 0, byteArray.Length);

            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
            }


        }
    }
}
 