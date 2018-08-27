

#include <SoftwareSerial.h>









int naklonX;
int naklonY;


void setup() {

	AccelSetup();

	Serial.begin(76800);


}

void loop()
{
	naklonX = getAccelX(); //крен лево-право
	naklonY = getAccelY(); //нос-кормма

	Serial.println(naklonX);
}



void motAccel() 
{



}


void printStatus(String text, int status) 
{

}


