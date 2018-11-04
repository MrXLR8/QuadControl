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
	const int MIN_POWER = 1000;
	const int MAX_POWER = 2000;
	int _m1, _m2, _m3, _m4;
	Servo m1, m2, m3, m4;
	int hardLimit;
	bool motorStatus = false;
	F_ESC(int m1pin, int m2pin, int m3pin, int m4pin) 
	{
		_m1 = m1pin;
		_m2 = m2pin;
		_m3 = m3pin;
		_m4 = m4pin;

		Serial.print("Attaching motors MIN: ");
		Serial.print(MIN_POWER);
		Serial.print("| MAX: ");
		Serial.println(MAX_POWER);
		Serial.print("Motor 1 are: ");
		Serial.println(_m1);
		


	}

	void Calibrate(int delayE,int _hard)
	{
		motorStatus = true;

		hardLimit = _hard;
		delay(delayE);
		Serial.println("Calibrating ESC");

		m1.attach(_m1, MIN_POWER, MAX_POWER);
		m2.attach(_m2, MIN_POWER, MAX_POWER);
		m3.attach(_m3, MIN_POWER, MAX_POWER);
		m4.attach(_m4, MIN_POWER, MAX_POWER);

		delay(delayE);
		Serial.print("Setting MIN: ");
		Serial.println(MIN_POWER);
		//m1.writeMicroseconds(MIN_POWER);
		//m2.writeMicroseconds(MIN_POWER);
		m3.writeMicroseconds(MIN_POWER); //бнглнфмн рнкэйн онрнлс врн нм ашк ондйкчвем!!!!
		//m4.writeMicroseconds(MIN_POWER);
		
		delay(10000);


		Serial.println("ESC CALIBARATION COMPLETED!");
		//motorStatus = false;

	}

	void motorAllow(bool status) 
	{
		motorStatus = status;
		if (!status) 
		{
			m1.writeMicroseconds(MIN_POWER);
			m2.writeMicroseconds(MIN_POWER);
			m3.writeMicroseconds(MIN_POWER);
			m4.writeMicroseconds(MIN_POWER);
		}
	}

	void set(int motor, int power) 
	{
		if (!motorStatus) return;
		int realpower = map(power, 0, 100, MIN_POWER, hardLimit);
		Serial.print(motor);
		Serial.print(":");
		Serial.println(realpower);
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
		int realpower = map(all, 0, 100, MIN_POWER, hardLimit);

		m1.writeMicroseconds(realpower);
		m2.writeMicroseconds(realpower);
		m3.writeMicroseconds(realpower);
		m4.writeMicroseconds(realpower);
	}
};

#endif

