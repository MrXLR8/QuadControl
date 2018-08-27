using System;
using System.Collections.Generic;
using System.Text;

namespace ArduinoProject.Shared
{
    public delegate void voidDelegate();
    public delegate void boolDelegate(bool status);
    public delegate void stringDelegate(string str);
    public delegate void intDelegate(int integer);
    public delegate void DintDelegate(int integer1,int integer2);
    public static class Variable
    {

        public static string bluetoothName = "HC-05";
    }
}
