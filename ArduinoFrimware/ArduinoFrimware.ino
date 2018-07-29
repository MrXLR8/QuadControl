
#include <SoftwareSerial.h>




int motor = 10;


#pragma region  bluetooth

int gRxPin = 13;
int gTxPin = 12;

bool bluetoothStatus = false;
#pragma endregion



SoftwareSerial BTSerial(gRxPin, gTxPin);


void setup() {


	BTSerial.setTimeout(500);
	BTSerial.begin(9600);

	Serial.begin(9600);
	delay(250);

}

void loop()
{

	//bluetoothM();
	//powerchange();
	powerset();
	powersetusb();

	
}
int val;
int bt = 0;
int calc = 0;
void powerset()
{



	if (BTSerial.available())
	{

		bt = BTSerial.read();
		BTSerial.write(bt);

		Serial.print("BT DATA: ");
		Serial.println(bt);


		if (bt != -1 & bt<=255)
		{

			analogWrite(motor, bt);
			Serial.print("Setting power: ");
			Serial.println(bt);
		}
		BTSerial.flush();
	}
}
int usb = 0;

void powersetusb()
{
	if (Serial.available()) {
		usb = Serial.read();


		if (usb != -1)
		{
			Serial.println(bt);
			usb -= 48;

			calc = usb * 28;
			analogWrite(motor, calc);
			Serial.print("Setting USB power: ");
			Serial.println(calc);
		}
		Serial.flush();
	}
}


