
#include "F_ESC.h"
#include "WiFiTimingFilter.h"
#include "TimePassed.h"
#include "Stabilize.h"
#include <MPU6050_tockn.h>

#include <Servo.h>
#include "Variables.h"
#include <StandardCplusplus.h>
#include "Order.h"
#include <SoftwareSerial.h>

SoftwareSerial wifi(8, 7);
SoftwareSerial* Order::wifi;

SoftwareSerial* WiFiTimingFilter::WiFi;
WiFiTimingFilter SendTimer;


MPU6050 mpu6050(Wire);

MPU6050* Order::mpu6050;
F_ESC* Order::ESC;


MPU6050* Stabilize::gyro;

Stabilize::Angle Stabilize::currentVector;
Stabilize::Angle Stabilize::requiredVector;
Stabilize::Angle Stabilize::stableVector;





int Stabilize::middlePower = 50;
Stabilize::Motors Stabilize::last(50, 50, 50, 50);

F_ESC ESC(9, 6, 5, 3);
void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("Booting...");

	// set the data rate for the SoftwareSerial port
	Order::wifi = &wifi;
	Order::ESC = &ESC;
	WiFiTimingFilter::WiFi = &wifi;

	Order::mpu6050 = &mpu6050;

	Stabilize::gyro = &mpu6050;
	

	wifi.begin(9600);
	ESC.Calibrate(3000, 1000, 2000, 1350);
	mpu6050.calcGyroOffsets(true);
	mpu6050.begin();


	Stabilize::start();

	

	Serial.println("");
	
	


	Serial.println("Start");
	digitalWrite(LED_BUILTIN, LOW);

}

String buffer = "";
char c;
void loop()
{
	mpu6050.update();

	sendGyroData();
	sendMotorData();

	SendTimer.proceed();

	if (wifi.available())
	{

		while (wifi.available())
		{
			c = wifi.read();
			
			buffer += c;
			if ((int)c == 10) break;
			
		}
		int lastchar = (int)buffer[buffer.length() - 1];


		if (buffer[0] == '['&lastchar==10)
		{
			Order recived;
			recived.Parse(buffer);
			recived.Execute();
		}
		else {
			Serial.print("BAD: ");
			Serial.println(buffer);
		}
		buffer = "";
	}

}


TimePassed gyroTime;
void sendGyroData()
{
	if (gyroTime.passed(50))
	{

		static String lastP, lastR;
		Stabilize::Angle accel = Stabilize::getAccel();
		String _pitch = String(int(accel.pitch));
		String _roll = String(int(accel.roll));
		if (lastP == _pitch && lastR == _roll)
		{
			return;
		}
		String toSend = "[GD]" + _pitch + "." + _roll;
		/*Order gyroData;
		gyroData.type = "GD";
		gyroData.content.push_back(_pitch);
		gyroData.content.push_back(_roll);*/



		//Serial.println(toSend);
		//Order::wifi->println(toSend);
		SendTimer.addString(toSend);
		lastP = _pitch;
		lastR = _roll;
	}

}

TimePassed motorime;
void sendMotorData()
{
	if (motorime.passed(50))
	{
		Stabilize::Motors toSend = Stabilize::StabIt();

		if (toSend == Stabilize::last) return;
		
		ESC.SetAll(toSend);
		Order MotorData;
		MotorData.type = "MD";
		MotorData.content.push_back(String(toSend.m1));
		MotorData.content.push_back(String(toSend.m2));
		MotorData.content.push_back(String(toSend.m3));
		MotorData.content.push_back(String(toSend.m4));

		Stabilize::last = toSend;

		SendTimer.addString(MotorData.ToString());
		//	Order::wifi->println(MotorData.ToString());
			//Serial.println(MotorData.ToString());
	}

}

void serialecho() {
	if (Serial.available())
	{
		String Sbuffer = "";
		Sbuffer = Serial.readString();

		Serial.println(Sbuffer);
		Order::wifi->println(Sbuffer);
	}

}



