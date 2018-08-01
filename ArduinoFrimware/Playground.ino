
#include "F_LCD.h"
#include "F_Joystick.h"
#include "F_Joystick.h"


F_Joystick joystick(A0, A1,2, true);
F_LCD display(20, 4);

void setup()
{

	pinMode(13, OUTPUT);
	display.start();
}
int cords[2];
void loop()
{
	delay(100);
	digitalWrite(13, HIGH);
	Vector2D data;
	data = joystick.position();

	cords[0] = data.x;
	cords[1] = data.y;
	display.clear();
	display.printValues(0, cords, 2);
	display.printValue(2, "Pressed?", joystick.pressed());
	

	delay(100);
	digitalWrite(13, LOW);
}





