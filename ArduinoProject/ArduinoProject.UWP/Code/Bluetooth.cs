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
        public static StreamSocket _socket;
        public static RfcommDeviceService _service;
        private static Windows.Foundation.IAsyncOperation<BluetoothDevice> device_task;
        public static BluetoothDevice device;

        private static async Task Start()
        {

            var serviceInfoCollection = await DeviceInformation.FindAllAsync
                (
                RfcommDeviceService.GetDeviceSelector(RfcommServiceId.SerialPort),
                new string[] { "System.Devices.AepService.AepId" } 
                ); // список всех устройств с поддержкой серийного порта

            foreach (var serviceInfo in serviceInfoCollection)
            {
                var deviceInfo = await DeviceInformation.CreateFromIdAsync
                    (
                    (string)serviceInfo.Properties["System.Devices.AepService.AepId"]
                    );


                if (deviceInfo.Name == "HC-05")
                {
                    device_task =  BluetoothDevice.FromIdAsync(deviceInfo.Id);  //поиск нужного нам устройства
                    break; 
                }
            } 
   
            await ConnectDevice();
        }

        public static async Task ConnectDevice()
        {
            device = await device_task;
            FormAction.print("Bluetooth Идентификатор получен для: " + device.Name);
            var result = await device.GetRfcommServicesForIdAsync(RfcommServiceId.SerialPort, BluetoothCacheMode.Uncached);
            _service = result.Services[0]; // получение Rfcomm серийного сервиса
            FormAction.print("Rfcomm сервис создан " + _service.Device.Name);

            _socket = new StreamSocket();
            await _socket.ConnectAsync(_service.ConnectionHostName, _service.ConnectionServiceName, SocketProtectionLevel.BluetoothEncryptionAllowNullAuthentication);
            FormAction.print("Сокет создан!");
        }

        public static async Task SendAsync(string str)
        {
            if (_service == null) { await Start(); }


            FormAction.print("Отправляю строку:");
            FormAction.print("> " + str);
            if (_socket != null)
            {

                byte[] byteArray = Encoding.UTF8.GetBytes(str);

                var writer = new DataWriter(_socket.OutputStream);

                writer.WriteString(str);

                // Launch an async task to 
                //complete the write operation
                await writer.StoreAsync();



            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
            }

        }

        public static async Task SendAsync(int number)
        {
            string str = number.ToString();

            if (_service == null) { await Start(); }


            FormAction.print("Отправляю строку:");
            FormAction.print("> " + str);
            if (_socket != null)
            {

                byte[] byteArray = Encoding.UTF8.GetBytes(str);

                var writer = new DataWriter(_socket.OutputStream);

                writer.WriteString(str);

                // Launch an async task to 
                //complete the write operation
                await writer.StoreAsync();



            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
            }
        }
    }
}
 