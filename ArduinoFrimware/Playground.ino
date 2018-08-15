#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13);


void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(76800);



	// set the data rate for the SoftwareSerial port
	mySerial.begin(76800);

	Serial.println("start");

}

void loop() { // run over and over

	if (mySerial.available()) {
		String buffer = "";
		while (mySerial.available())
		{
			char c = mySerial.read();
			buffer += c;

		}
		Serial.print(buffer);
	}

}