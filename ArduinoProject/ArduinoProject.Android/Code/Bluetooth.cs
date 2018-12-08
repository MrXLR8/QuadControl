using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Android.App;
using Android.Bluetooth;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using ArduinoProject.Code;

namespace ArduinoProject.Shared
{
    public static partial class Bluetooth
    {
        
        private static BluetoothAdapter adapter = BluetoothAdapter.DefaultAdapter;
        private static BluetoothSocket _socket;
        private static async Task Start()
        {

            if (adapter == null)
            {
                FormAction.printRecivedData("[ОШИБКА]: Bluetooth не найден");
                return;
            }
            if (!adapter.IsEnabled)
            {
                FormAction.printRecivedData("[ОШИБКА]: Bluetooth выключен");
                return;
            }
            await ConnectDevice();

        }

        public static async Task ConnectDevice()
        {
           

            if (adapter == null)
            {
                return;
            }
            FormAction.printRecivedData("Подключаюсь к устройству");
            BluetoothDevice device =
                (from bd in adapter.BondedDevices
                 where bd.Name == Variable.bluetoothName
                 select bd).FirstOrDefault(); // получения устройства по имени из всех спарированых

            if (device == null)
            {
                FormAction.printRecivedData("[ОШИБКА]: Не удалось подключиться к " + Variable.bluetoothName);
                return;
            }
            else
                FormAction.printRecivedData("Подключилься к " + device.Name); 
            _socket = device.CreateRfcommSocketToServiceRecord(Java.Util.UUID.FromString("00001101-0000-1000-8000-00805f9b34fb")); // ID Серийного соединения
            
            adapter.CancelDiscovery();
            try
            {
               await _socket.ConnectAsync();
            }
            catch (Exception e)
            {
                FormAction.printRecivedData("[ОШИБКА]: Неудалось соединиться с утройством. Причина: " + e.Message);
                return;
            }
            return;
        }

     

        public static async Task Send(int number)
        {
            if (_socket == null)
            {
                 await Start();
            }
            


            FormAction.printRecivedData("Отправляю число:");
            FormAction.printRecivedData("> " + number);
            if (_socket!=null&&_socket.IsConnected)
            {

                byte _byte = Convert.ToByte(number);

                _socket.OutputStream.WriteByte(_byte);
                return;
            }
            else
            {
                FormAction.printRecivedData("[ОШИБКА]: Соеденение не было установлено.");
                return;
            }

        }



    }
}