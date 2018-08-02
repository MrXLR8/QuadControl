
#include "F_LCD.h"
#include "F_MPU6050.h"

F_LCD display(20, 4);
F_MPU6050 accel;

void setup()
{

	pinMode(13, OUTPUT);
	display.start();
	accel.start();
	Serial.println("asd");
	
}
int cords[2];
int gyroc[2];
xyz data;
xyz gyro;
void loop()
{


	data=accel.getAccelXYZ();



	cords[0] = data.x;
	cords[1] = data.y;
	cords[2] = data.z;

	display.clear();
	display.printValues(0, cords, 3);



	delay(200);
}





