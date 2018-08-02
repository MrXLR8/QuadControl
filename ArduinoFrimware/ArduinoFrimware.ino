
#include "F_MPU6050.h"
#include <SoftwareSerial.h>




int motor1 = 10;
int motor2 = 9;

int motor3 = 6;
int motor4 = 5;


#pragma region  bluetooth

int gRxPin = 12;
int gTxPin = 11;
int onboard_led = 13;
bool bluetoothStatus = false;
#pragma endregion



SoftwareSerial BTSerial(gRxPin, gTxPin);


void setup() {

	AccelSetup();
	pinMode(onboard_led, OUTPUT);
	
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(motor3, OUTPUT);
	pinMode(motor4, OUTPUT);


	BTSerial.setTimeout(500);
	BTSerial.begin(9600);

	Serial.begin(9600);
	delay(250);

}

void loop()
{
	digitalWrite(13, HIGH);
	delay(100);
	//bluetoothM();
	//powerchange();
	powerset();
	powersetusb();
	analogWrite(motor1, 50);

	//motAccel();
	digitalWrite(13, LOW);
	delay(100);

	
}

int naklonX;
int naklonY;

int motorPower1;
int motorPower2;
int motorPower3;
int motorPower4;

void motAccel() 
{
	naklonX = getAccelX(); //крен лево-право
	naklonY = getAccelY(); //нос-кормма

	
	

	motorPower1 =map(constrain(naklonX, 5, 90), 5, 90, 0, 250);
	motorPower2 = map(constrain(naklonX, -90, -5), -5, -90, 0, 250);

	motorPower3 = map(constrain(naklonY, 5, 90), 5, 90, 0, 250);
	motorPower4 = map(constrain(naklonY, -90, -5), -5, -90, 0, 250);

	printStatus("motorPower1", motorPower1);
	printStatus("motorPower2", motorPower2);

	printStatus("motorPower3", motorPower3);
	printStatus("motorPower4", motorPower4);

	Serial.println("//---------\\");


	analogWrite(motor1, motorPower1);
	analogWrite(motor2, motorPower2);

	analogWrite(motor3, motorPower3);
	analogWrite(motor4, motorPower4);

}


void printStatus(String text, int status) 
{
	Serial.print(text + ": ");
	Serial.println(status);
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

			analogWrite(motor1, bt);
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
			analogWrite(motor1, calc);
			Serial.print("Setting USB power: ");
			Serial.println(calc);
		}
		Serial.flush();
	}
}


