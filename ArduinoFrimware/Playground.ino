#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "I2Cdev.h"
#include "MPU6050.h"





void setup()
{
	DisplaySetup();
	AccelSetup();

}
void loop()
{
	DisplayClear();
	DisplayPrintXYZ(1, getAccelX(), getAccelY(), getAccelZ());

	delay(200);
}





