


#include "Variables.h"
#include <StandardCplusplus.h>
#include "Order.h"
#include <SoftwareSerial.h>

SoftwareSerial wifi(12, 13);
SoftwareSerial* Order::wifi;

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(76800);



	// set the data rate for the SoftwareSerial port
	Order::wifi = &wifi;
	wifi.begin(76800);

	Serial.println("start");

}

void loop() 
{ // run over and over

	if (wifi.available()) {
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
	
	serialecho();
	
	
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