using System;
using System.Collections.Generic;
using System.Text;

namespace ArduinoProject.Shared
{
    public delegate void voidDeleagate();
    public delegate void boolDeleagate(bool status);
    public delegate void stringDelegate(string str);

    public static class Variable
    {

        public static string bluetoothName = "HC-05";
    }
}
