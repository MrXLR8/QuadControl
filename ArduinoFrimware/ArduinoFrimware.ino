
#include "F_ESC.h"
#include "WiFiTimingFilter.h"
#include "TimePassed.h"
#include "Stabilize.h"
#include <MPU6050_tockn.h>


#include <Servo.h>
#include <StandardCplusplus.h>
#include "Order.h"



#define MIN_POWER 1000
#define MAX_POWER 2000

#pragma region Wifi_Vars


WiFiTimingFilter SendTimer;

#pragma endregion
#pragma region MPU_Vars


MPU6050* Stabilize::gyro;
MPU6050 mpu6050(Wire);
MPU6050* Order::mpu6050;
#pragma endregion

F_ESC* Order::ESC;
F_ESC ESC(9, 6, 5, 3);


#pragma region  Stabilizing_Vars

Stabilize::Angle Stabilize::currentVector;
Stabilize::Angle Stabilize::requiredVector;
Stabilize::Angle Stabilize::stableVector;

int Stabilize::middlePower = 50;
Stabilize::Motors Stabilize::last(50, 50, 50, 50);

Stabilize::Motors Stabilized;
#pragma endregion

Servo test;
bool blink = true;
void setup() {

	Serial.begin(9600);
	
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH); // тухнет если не завис при запуске
	Serial.println("Booting...");

	//ѕередача переменной Wi-Fi
	Order::ESC = &ESC;


	//ѕередача переменной √ироскопа
	Order::mpu6050 = &mpu6050;
	Stabilize::gyro = &mpu6050;

	
	mpu6050.calcGyroOffsets(true);
	mpu6050.begin();
	Serial.println();
	

#pragma region testMotor


	test.attach(5, MIN_POWER, MAX_POWER);
	Serial.println("Setting ");
	delay(3000);

	Serial.println("Setting MIN: ");
	test.write(1000);
	delay(8000);

#pragma endregion
	//ESC.Calibrate(10000, 1300); //калибровка с задержкой {1}, но чтобы не сгорел ограничить в {2}



	


	Stabilize::start(10); // “€га моторов когда в ровном положении.


	Serial.println("");

	Serial.println("Start");
	digitalWrite(LED_BUILTIN, LOW);

}

String buffer = "";
char c;
void loop()
{
	digitalWrite(LED_BUILTIN, blink ? HIGH : LOW);
	blink = !blink;

	mpu6050.update();

	sendGyroData();
	sendMotorData();
	setMotors();
	SendTimer.proceed();
	getWifiOrder();

	
}

void getWifiOrder() 
{
	if (Serial.available())
	{

		while (Serial.available())
		{
			c = Serial.read();

			buffer += c;
			if ((int)c == 10) break;

		}

		int lastchar = (int)buffer[buffer.length() - 1];


		if (buffer[0] == '['&lastchar == 10)
		{
			Order recived;
			recived.Parse(buffer);
			recived.Execute();
		}
		/*
		else {
			Serial.print("BAD: ");
			Serial.println(buffer);
		}
		*/
		buffer = "";
	}
}
void setMotors() 
{
	/*
	if (Stabilized == Stabilize::last) return;

	ESC.SetAll(Stabilized);
	*/
	int randomI = random(1020, 1050);
	test.write(randomI);
	delay(200);
}

TimePassed gyroTime;
void sendGyroData()
{
	if (gyroTime.passed(50))
	{

		static String lastP, lastR;
		Stabilize::Angle accel = Stabilize::getAccel();
		String _pitch = String(int(accel.pitch));
		String _roll = String(int(accel.roll));
		if (lastP == _pitch && lastR == _roll)
		{
			return;
		}
		String toSend = "[GD]" + _pitch + "." + _roll;

		SendTimer.addString(toSend);
		lastP = _pitch;
		lastR = _roll;
	}

}

TimePassed motorime;
void sendMotorData()
{
	Stabilized = Stabilize::StabIt();
	if (motorime.passed(50))
	{

		Order MotorData;
		MotorData.type = "MD";
		MotorData.content.push_back(String(Stabilized.m1));
		MotorData.content.push_back(String(Stabilized.m2));
		MotorData.content.push_back(String(Stabilized.m3));
		MotorData.content.push_back(String(Stabilized.m4));

		Stabilize::last = Stabilized;

		SendTimer.addString(MotorData.ToString());
		//	Order::wifi->println(MotorData.ToString());
			//Serial.println(MotorData.ToString());
	}

}







