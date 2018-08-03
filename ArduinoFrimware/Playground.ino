
#include "F_LCD.h"
#include "F_MPU6050.h"

F_LCD display(20, 4);
F_MPU6050 accel;

void setup()
{

	pinMode(13, OUTPUT);
	display.start();
	accel.start();
	
}
int cords[2];
Angle data;
long loop_timer;
void loop()
{


	data=accel.getGyro();



	cords[0] = data.pitch;
	cords[1] = data.roll;

	display.clear();
	display.printValues(0, cords, 3);

	delay(200);

}







