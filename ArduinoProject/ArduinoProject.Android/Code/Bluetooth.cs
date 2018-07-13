using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
        const string deviceName = "HC-05";
        private static BluetoothAdapter adapter = BluetoothAdapter.DefaultAdapter;
        private static BluetoothSocket _socket;
        private static bool Start()
        {

            if (adapter == null)
            {

                FormAction.print("[ОШИБКА]: Bluetooth не найден");
                return false;
            }

            if (!adapter.IsEnabled)
            {
                FormAction.print("[ОШИБКА]: Bluetooth выключен");
                return false;
            }

            return true;

        }

        public static bool ConnectDevice()
        {
            if (adapter == null)
            {
                if(!Start()) { return false; }
            }
            FormAction.print("Подключаюсь к устройству");
            BluetoothDevice device =
                (from bd in adapter.BondedDevices
                 where bd.Name == deviceName
                 select bd).FirstOrDefault();

            if (device == null)
            {
                FormAction.print("[ОШИБКА]: Не удалось подключиться к " + deviceName);
                return false;
            }
            else
                FormAction.print("Подключилься к " + device.Name); 


            _socket = device.CreateRfcommSocketToServiceRecord(Java.Util.UUID.FromString("00001101-0000-1000-8000-00805f9b34fb"));

            adapter.CancelDiscovery();
            try
            {
                _socket.Connect();
            }
            catch (Exception e)
            {
                FormAction.print("[ОШИБКА]: Неудалось соединиться с утройством. Причина: " + e.Message);
                return false;
            }
            return true;

        }

        public static bool Send(string str)
        {
            if(_socket==null)
            {
                if(!ConnectDevice())
                {
                    FormAction.print("[ОШИБКА]: Отправка не удалась");
                    return false;
                }
            }


            FormAction.print("Отправляю строку:");
            FormAction.print("> "+str);
            if (_socket.IsConnected)
            {

                byte[] byteArray = Encoding.UTF8.GetBytes(str);
                _socket.OutputStream.Write(byteArray, 0, byteArray.Length);
                return true;
            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
                return false;
            }
            
        }

        public static bool Send(int number)
        {
            if (_socket == null)
            {
                if (!ConnectDevice())
                {
                    FormAction.print("[ОШИБКА]: Отправка не удалась");
                    return false;
                }
            }


            FormAction.print("Отправляю число:");
            FormAction.print("> " + number);
            if (_socket.IsConnected)
            {

                byte[] byteArray = Encoding.UTF8.GetBytes(number.ToString());
                _socket.OutputStream.Write(byteArray, 0, byteArray.Length);
                return true;
            }
            else
            {
                FormAction.print("[ОШИБКА]: Соеденение не было установлено.");
                return false;
            }

        }



    }
}