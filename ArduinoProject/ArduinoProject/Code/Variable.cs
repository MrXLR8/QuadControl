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
    public delegate void QintDelegate(int integer1, int integer2,int integer3,int integer4);
    public static class Variable
    {

        public static string bluetoothName = "HC-05";
        public static int middlePower = 50;
    }
    public static class Method
    {
        public static int map(int x, int in_min, int in_max, int out_min, int out_max)
        {
            int res = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
            if (res > out_max) return out_max;
            if (res < out_min) return out_min;
            return res;
        }
    }
}
