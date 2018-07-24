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
        private static void Start()
        {

            if (adapter == null)
            {
                FormAction.print("[ОШИБКА]: Bluetooth не найден");
                return;
            }
            if (!adapter.IsEnabled)
            {
                FormAction.print("[ОШИБКА]: Bluetooth выключен");
                return;
            }
            return;
        }

        public static async Task ConnectDevice()
        {
            Start();

            if (adapter == null)
            {
                return;
            }
            FormAction.print("Подключаюсь к устройству");
            BluetoothDevice device =
                (from bd in adapter.BondedDevices
                 where bd.Name == Variable.bluetoothName
                 select bd).FirstOrDefault(); // получения устройства по имени из всех спарированых

            if (device == null)
            {
                FormAction.print("[ОШИБКА]: Не удалось подключиться к " + Variable.bluetoothName);
                return;
            }
            else
                FormAction.print("Подключилься к " + device.Name); 
            _socket = device.CreateRfcommSocketToServiceRecord(Java.Util.UUID.FromString("00001101-0000-1000-8000-00805f9b34fb")); // ID Серийного соединения
            
            adapter.CancelDiscovery();
            try
            {
               await _socket.ConnectAsync();
            }
            catch (Exception e)
            {
                FormAction.print("[ОШИБКА]: Неудалось соединиться с утройством. Причина: " + e.Message);
                return;
            }
            return;
        }

     

        public static async Task Send(int number)
        {
            if (_socket == null)
            {
                 await ConnectDevice();
            }
            


            FormAction.print("Отправляю число:");
            FormAction.print("> " + number);
            if (_socket.IsConnected)
            {

                byte _byte = Convert.ToByte(number);

                _socket.OutputStream.WriteByte(_byte);
                return;
            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
                return;
            }

        }



    }
}