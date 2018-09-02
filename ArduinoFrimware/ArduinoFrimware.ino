#include "F_MPU_TOCKN.h"
#include "WiFiTimingFilter.h"
#include "TimePassed.h"
#include "Stabilize.h"
#include <MPU6050_tockn.h>


#include "Variables.h"
#include <StandardCplusplus.h>
#include "Order.h"
#include <SoftwareSerial.h>

SoftwareSerial wifi(11, 12);
SoftwareSerial* Order::wifi;

SoftwareSerial* WiFiTimingFilter::WiFi;
WiFiTimingFilter SendTimer;


MPU6050 mpu6050(Wire);

MPU6050* Order::mpu6050;


MPU6050* Stabilize::gyro;

Stabilize::Angle Stabilize::currentVector;
Stabilize::Angle Stabilize::requiredVector;
Stabilize::Angle Stabilize::stableVector;
int Stabilize::middlePower = 50;
Stabilize::Motors Stabilize::last(50, 50, 50, 50);
void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(76800);



	// set the data rate for the SoftwareSerial port
	Order::wifi = &wifi;
	WiFiTimingFilter::WiFi = &wifi;

	Order::mpu6050 = &mpu6050;

	Stabilize::gyro = &mpu6050;
	Stabilize::start();

	wifi.begin(76800);

	Order::mpu6050->begin();
	Order::mpu6050->calcGyroOffsets(true);

	Serial.println("start");

}

void loop()
{
	mpu6050.update();

	sendGyroData();
	sendMotorData();

	SendTimer.proceed();

	if (wifi.available())
	{
		String buffer = "";
		while (wifi.available())
		{
			char c = wifi.read();
			buffer += c;
		}


		if (buffer[0] == '[')
		{
			Order recived;
			recived.Parse(buffer);
			recived.Execute();
		}
	}

}


TimePassed gyroTime;
void sendGyroData()
{
	if (gyroTime.passed(30))
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
	if (motorime.passed(30))
	{
		Stabilize::Motors toSend = Stabilize::StabIt();

		if (toSend == Stabilize::last) return;
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



