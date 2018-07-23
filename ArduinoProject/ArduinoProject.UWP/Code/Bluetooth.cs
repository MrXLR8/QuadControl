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
using Windows.Devices.Radios;
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


        public static async Task<bool> GetBluetoothIsEnabledAsync()
        {
            var radios = await Radio.GetRadiosAsync();
            var bluetoothRadio = radios.FirstOrDefault(radio => radio.Kind == RadioKind.Bluetooth);
            return bluetoothRadio != null && bluetoothRadio.State == RadioState.On;
        }

        private static async Task Start()
        {
            if (!(await GetBluetoothIsEnabledAsync()))
            {
                FormAction.print("[ОШИБКА] Bluetooth отключён");
                return;
            }
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


                if (deviceInfo.Name == Variable.bluetoothName)
                {
                    device_task =  BluetoothDevice.FromIdAsync(deviceInfo.Id);  //поиск нужного нам устройства
                    break; 
                }
            } 
   
            await ConnectDevice();
        }

        public static async Task ConnectDevice()
        {
            if (device_task == null)
            {
                FormAction.print("[ОШИБКА]: "+ Variable.bluetoothName + " не сопряжен или не найден");
                return;
            }
            else
            {
                device = await device_task;
            }
            
            FormAction.print("Bluetooth споряжение найдено для: " + device.Name);
            RfcommDeviceServicesResult result = await device.GetRfcommServicesForIdAsync(RfcommServiceId.SerialPort, BluetoothCacheMode.Uncached);


            if(result.Services.Count==0)
            {
                FormAction.print("[ОШИБКА] Не удалось подключиться к Bluetooth устройству: " + device.Name + "// "+ "или устоойство не поддерживает выбранный сервис");
                return;
            }
            _service = result.Services[0];


            FormAction.print("Подключение к устройству успешно: " + _service.Device.Name);

            _socket = new StreamSocket();
            await _socket.ConnectAsync(_service.ConnectionHostName, _service.ConnectionServiceName, SocketProtectionLevel.BluetoothEncryptionAllowNullAuthentication);
        }

        public static async Task Send(string str)
        {
            if (_service == null) { await Start(); }



            if (_socket != null)
            {
                FormAction.print("Отправляю строку:");
                FormAction.print("> " + str);
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

        public static async Task Send(int number)
        {

            if (_service == null) { await Start(); }



            if (_socket != null)
            {
                FormAction.print("> " + number);


                var writer = new DataWriter(_socket.OutputStream);

                writer.WriteByte(Convert.ToByte(number));

                StartListening();

                // Launch an async task to 
                //complete the write operation
                await writer.StoreAsync();



            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
            }
        }


        //public static async Task StartListening()
        //{
        //    DataReader rx = new DataReader(_socket.InputStream);
        //    bool SocketStatus = false;
        //    uint bytesLoaded;
        //    do
        //    {
        //        bytesLoaded = await rx.LoadAsync(20);
        //        SocketStatus = Convert.ToBoolean(bytesLoaded);
        //        var symbol = rx.ReadString(bytesLoaded);
        //        FormAction.print("<" + symbol);
        //    } while (SocketStatus);

        //    FormAction.print("[ОШИБКА]: Соеденение закрыто");


        //}


        public static async Task StartListening()
        {
            DataReader rx = new DataReader(_socket.InputStream);
            bool SocketStatus = false;
            uint bytesLoaded;
            do
            {
                bytesLoaded = await rx.LoadAsync(1);
                SocketStatus = Convert.ToBoolean(bytesLoaded);
                var symbol = rx.ReadByte();
                FormAction.print("<" + symbol);
            } while (SocketStatus);

            FormAction.print("[ОШИБКА]: Соеденение закрыто");


        }

    }
}
 