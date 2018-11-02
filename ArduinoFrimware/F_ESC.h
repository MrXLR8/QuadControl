// F_ESC.h
#include <Servo.h>
#include "Stabilize.h"
#ifndef _F_ESC_h
#define _F_ESC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class F_ESC {
public:
	Servo m1, m2, m3, m4;
	int powerMin, powerMax;
	int hardLimit;
	bool motorStatus = false;
	F_ESC(int m1pin, int m2pin, int m3pin, int m4pin) 
	{
		m1.attach(m1pin);
		m2.attach(m2pin);
		m3.attach(m3pin);
		m4.attach(m4pin);
	}

	void Calibrate(int delayE,int min,int max,int _hard)
	{
		motorStatus = true;
		hardLimit = max;

		Serial.print("Calibrating ESC (");
		Serial.print(min);
		Serial.print("-");
		Serial.print(max);
		Serial.println(")");

		Serial.print("Setting MAX: ");
		Serial.println(max);
		SetAll(100);
		delay(delayE);



		Serial.print("Setting MIN: ");
		Serial.println(min);
		SetAll(0);
		delay(delayE);


		Serial.println("ESC CALIBARATION COMPLETED!");
		motorStatus = false;

	}

	void motorAllow(bool status) 
	{
		motorStatus = status;
	}

	void set(int motor, int power) 
	{
		if (!motorStatus) return;
		int realpower = map(power, 0, 100, powerMin, hardLimit);

		switch (motor)
		{
		case 1:
			m1.writeMicroseconds(realpower);
			break;
		case 2:
			m2.writeMicroseconds(realpower);
			break;
		case 3:
			m3.writeMicroseconds(realpower);
			break;
		case 4:
			m4.writeMicroseconds(realpower);
			break;
		default:
			break;
		}
	}

	void SetAll(Stabilize::Motors _data) 
	{
		if (!motorStatus) return;
		set(1, _data.m1);
		set(2, _data.m2);
		set(3, _data.m3);
		set(4, _data.m4);

		Serial.print("MOTORS: ");
		Serial.print(_data.m1);
		Serial.print("|");
		Serial.print(_data.m2);
		Serial.print("|");
		Serial.print(_data.m3);
		Serial.print("|");
		Serial.println(_data.m4);
	}

	void SetAll(int all) 
	{
		if (!motorStatus) return;
		int realpower = map(all, 0, 100, powerMin, hardLimit);

		m1.writeMicroseconds(realpower);
		m2.writeMicroseconds(realpower);
		m3.writeMicroseconds(realpower);
		m4.writeMicroseconds(realpower);
	}
};

#endif

