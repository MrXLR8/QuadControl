#include "F_MPU6050.h"

F_MPU6050 gyro;
Angle ang;
void setup() 
{
	Serial.begin(76800);
	gyro.start();
}

void loop() 
{
	ang = gyro.getGyro();	
	Serial.println(ang.roll);
	delay(300);
}