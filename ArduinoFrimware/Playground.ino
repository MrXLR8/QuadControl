
#include "F_SD.h"
F_SD card(4);
void setup()
{
	
	Serial.println(card.start());


	card.WriteFile("CREATED2/created.txt", "info");
	
}

void loop()
{


	


}







