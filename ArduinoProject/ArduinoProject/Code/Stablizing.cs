using System;
using System.Collections.Generic;
using System.Text;

namespace ArduinoProject.Code
{
   public static class Stablizing
    {
        public enum Angle
        {
            Pitch,
            Roll
        }

        public static int MotorPower = 10;
        static int ReqPitch = 0;
        static int ReqRoll = 0;

        public static void AddRequest(Angle angle, int req)
        {
            switch(angle)
            {
                case Angle.Pitch:
                    ReqPitch += req;
                        break;

                case Angle.Roll:
                    ReqRoll += req;
                        break;
            }
        }

        public static void RemoveRequest(Angle angle, int req)
        {
            switch (angle)
            {
                case Angle.Pitch:
                    ReqPitch -= req;
                    break;

                case Angle.Roll:
                    ReqRoll -= req;
                    break;
            }
        }


        public static Order Form()
        {
            String[] angles = new String[3];
            angles[0] = ReqPitch.ToString();
            angles[1] = ReqRoll.ToString();
            angles[2] = MotorPower.ToString();
            return new Order("AC", angles);
        }


    }
}
