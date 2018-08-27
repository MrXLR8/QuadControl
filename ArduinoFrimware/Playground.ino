#include <MPU6050_tockn.h>


#include "F_MPU6050.h"
#include "Variables.h"
#include <StandardCplusplus.h>
#include "Order.h"
#include <SoftwareSerial.h>

SoftwareSerial wifi(11, 12);
SoftwareSerial* Order::wifi;

MPU6050 mpu6050(Wire);
MPU6050* Order::mpu6050;
void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(76800);


	
	// set the data rate for the SoftwareSerial port
	Order::wifi = &wifi;
	Order::mpu6050 = &mpu6050;
	wifi.begin(76800);

	Order::mpu6050->begin();
	Order::mpu6050->calcGyroOffsets(true);

	Serial.println("start");

}

void loop()
{ // run over and over
	mpu6050.update();

	if (millsPassed(200)) 
	{
		sendGyroData();
	}

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

	//sendGyroData();
}

void sendGyroData()
{

		mpu6050.update();
		String _pitch = String(int(mpu6050.getAngleX()));
		String _roll = String(int(mpu6050.getAngleY()));
		String toSend = "[GD]" + _pitch + "." + _roll;
		/*Order gyroData;
		gyroData.type = "GD";
		gyroData.content.push_back(_pitch);
		gyroData.content.push_back(_roll);*/
		Serial.println(toSend);
		Order::wifi->println(toSend);
		

}


int lastmills;
bool millsPassed(int delay) 
{
	int diff = millis() - lastmills;
	
	if (diff >= delay)
	{
		lastmills = millis(); return true;
	}
	return false;
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



//MPU6050 mpu6050(Wire);
//
//void setup() {
//	Serial.begin(9600);
//	Wire.begin();
//	mpu6050.begin();
//	mpu6050.calcGyroOffsets(true);
//}
//
//void loop() {
//	mpu6050.update();
//	Serial.print("angleX : ");
//	Serial.print(mpu6050.getAngleX());
//	Serial.print("\tangleY : ");
//	Serial.print(mpu6050.getAngleY());
//	Serial.print("\tangleZ : ");
//	Serial.println(mpu6050.getAngleZ());
//}
