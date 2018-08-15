using System;
using System.Collections.Generic;
using System.Text;

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
            if(str[0]=='['&str[3]==']')
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

        public Order(String _type, String[] _content)
        {
            if(_type.Length==2)
            {
                if(_content[0].Length>0)
                {
                    type = _type;
                    content = _content;
                }
            }
        }

        public Order() { }

        public override string ToString()
        {
            String result =  $"[{type}]";
            foreach(String s in content)
            {
                result += s;
                result += ".";
            }
            result=result.Remove(result.Length-1);
            return result;

        }


    }



}
