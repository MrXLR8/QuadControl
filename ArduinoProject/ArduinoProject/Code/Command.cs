using ArduinoProject.Shared;
using System;
using System.Collections.Generic;
using System.Text;
using System.Timers;
using Xamarin.Forms;

namespace ArduinoProject.Code
{
    public class Order
    {
        public String type;
        public String[] content;



        public static Order Parse(String str)
        {
            Order result = new Order();
            String type, body;
            if (str[0] == '[' & str[3] == ']')
            {
                type = str.Remove(0, 1);
                type = type.Remove(2);
                result.type = type;

                body = str.Remove(0, 4);
                result.content = body.Split('.');
            }
            else { return null; }

            return result;
        }


        public Order(String toParse)
        {

            if (toParse[0] == '[' & toParse[3] == ']')
            {
                type = toParse.Remove(0, 1);
                type = type.Remove(2);
                content = toParse.Remove(0, 4).Split('.');
            }

        }

        public Order(String _type, String[] _content)
        {
            if (_type.Length == 2)
            {
                if (_content[0].Length > 0)
                {
                    type = _type;
                    content = _content;
                }
            }
        }



        public Order() { }

        public override string ToString()
        {
            String result = $"[{type}]";
            foreach (String s in content)
            {
                result += s;
                result += ".";
            }
            result = result.Remove(result.Length - 1);
            return result;

        }


        public void Execute()
        {
            if (content.Length == 0) return;

            if (type == "WP")
            {
                new Ping(this);
            }


        }





    }


    public class Ping 
        {
        const int INTERVAL = 2;
        const int TIMEOUT = 1000;

        public static intDelegate pingFinished;
        public static voidDelegate staticStopCommand;

        public int mills;
        public Timer time = new Timer();

        Order sender;

        public Ping(Order _sender)
        {
            sender = _sender;
            if (sender.content[0] == "1") start();
            else if (sender.content[0] == "2") staticStopCommand?.Invoke();
        }

        public void start()
        {
            staticStopCommand = null;
            time?.Stop();
            SocketConnection.write(sender.ToString());

            mills = 0;
            time = new Timer();
            time.Interval = INTERVAL; // 5 milliseconds  
            time.Elapsed += Timer_Elapsed;
            time.Start();
            staticStopCommand = PingStopCommand;
        }

        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            mills += INTERVAL;
            if (mills > TIMEOUT) PingStopCommand();
        }

        private void PingStopCommand()
        {
            time.Stop();
            staticStopCommand = null;
            Device.BeginInvokeOnMainThread(() =>
            {
                pingFinished.Invoke(mills);
            });
        }

    }


}
