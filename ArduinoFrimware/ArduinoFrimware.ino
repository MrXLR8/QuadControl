
#include <SoftwareSerial.h>

int green = 6;
int yellow = 5;
int red = 3;

int buttonP = 9;
int buttonM = 8;

int motor = 10;

int power = 0;
int change = 2;

bool PressP;
bool PressM;

#pragma region  bluetooth

int gRxPin = 12;
int gTxPin = 13;

bool bluetoothStatus = false;
#pragma endregion



SoftwareSerial BTSerial(gRxPin, gTxPin);


void setup() {

	pinMode(green, OUTPUT);
	pinMode(yellow, OUTPUT);
	pinMode(red, OUTPUT);

	pinMode(buttonP, INPUT);
	pinMode(buttonM, INPUT);

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


		if (bt != -1)
		{

			bt -= 48;

			calc = bt * 28;
			analogWrite(motor, calc);
			Serial.print("Setting power: ");
			Serial.println(calc);
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
void bluetoothM()
{

	val = BTSerial.read();

	if (val == -1) {
		return;
	}
	Serial.println(val);



	// ��� ������� "1" �������� ���������
	if (val == 49)
	{

		digitalWrite(green, HIGH);
		digitalWrite(yellow, LOW);
		digitalWrite(red, LOW);

		BTSerial.write("Green is on!\n");

	}
	if (val == 50)
	{
		digitalWrite(green, LOW);
		digitalWrite(yellow, HIGH);
		digitalWrite(red, LOW);

		BTSerial.write("Yellow is on!\n");
	}
	if (val == 51)
	{
		digitalWrite(green, LOW);
		digitalWrite(yellow, LOW);
		digitalWrite(red, HIGH);

		BTSerial.write("Red is on!\n");
	}
	// ��� ������� "0" ��������� ���������
	if (val == 48)
	{
		digitalWrite(green, LOW);
		digitalWrite(yellow, LOW);
		digitalWrite(red, LOW);

		BTSerial.write("<OFF>>\n");
	}

}
void  powerchange()
{

	PressP = digitalRead(buttonP);
	PressM = digitalRead(buttonM);

	if (PressP)
	{
		addPower();
	}
	if (PressM)
	{
		decPower();
	}
	analogWrite(motor, power);
}


void addPower()
{
	if ((power + change) <= 250)
	{
		Serial.print("Adding Power. ");
		Serial.println(power);
		power += change;

	}
	else { Serial.println("Cant add Power"); }
}
void decPower()
{
	if ((power - change) >= 0)
	{
		Serial.print("Decreasing Power. ");
		Serial.println(power);
		power -= change;
	}
	else { Serial.println("Cant decrease Power"); }
}


