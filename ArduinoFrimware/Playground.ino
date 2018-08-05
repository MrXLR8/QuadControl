
#include "F_SonicRangefinder.h"
F_SonicRangefinder range(10, 11);

void setup()
{

}

void loop()
{

	Serial.println(range.getInch());
	delay(1000);
	


}







