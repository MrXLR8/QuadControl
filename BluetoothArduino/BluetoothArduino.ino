
#include <SoftwareSerial.h>

int green = 6;
int yellow = 5;
int red = 3;

int buttonP = 9;
int buttonM = 8;

int brightness = 10;
int change = 10;

bool PressP;
bool PressM;

int gRxPin = 10;
int gTxPin = 11;

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

		bluetoothM();
	
}
 int val;
void bluetoothM()
{

	val = BTSerial.read();

		if (val == -1) {
			return;
		}
		Serial.println(val);

	

	// При символе "1" включаем светодиод
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
	// При символе "0" выключаем светодиод
	if (val == 48)
	{
		digitalWrite(green, LOW);
		digitalWrite(yellow, LOW);
		digitalWrite(red, LOW);

		BTSerial.write("<OFF>>\n");
	}

}
void  brightchange()
{

	PressP = digitalRead(buttonP);
	PressM = digitalRead(buttonM);
	analogWrite(green, brightness);

	if (PressP)
	{
		addLight();
	}
	if (PressM)
	{
		minusLight();
	}

}


void addLight()
{
	if ((brightness + change) <= 250)
	{
		Serial.print("Adding Bright. ");
		Serial.println(brightness);
		brightness += change;
	}
	else { Serial.println("Cant add Bright"); }
}
void minusLight()
{
	if ((brightness - change) >= 0)
	{
		Serial.print("Decreasing Bright. ");
		Serial.println(brightness);
		brightness -= change;
	}
	else { Serial.println("Cant decrease Bright"); }
}


