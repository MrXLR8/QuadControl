
#include "F_SD.h"
F_SD card(4);
void setup()
{
	
	Serial.println(card.start());
	Serial.println(card.MbFree());
	
}

void loop()
{

	delay(1000);
	Serial.println("alive");
	


}







