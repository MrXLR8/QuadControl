// F_ESC.h

#include "Stabilize.h"
#include <Servo.h>
#ifndef _F_ESC_h
#define _F_ESC_h
#define MIN_POWER 1000
#define MAX_POWER 2000


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class F_ESC {
public:
	


	int hardLimit;


	F_ESC(int m1pin, int m2pin, int m3pin, int m4pin) 
	{
		_m1 = m1pin;
		_m2 = m2pin;
		_m3 = m3pin;
		_m4 = m4pin;
	}

	void Attach() 
	{
		Serial.println("Attaching ESC motors");
		motor[0].attach(_m2, MIN_POWER, MAX_POWER); // настроены так как подписаны на еск
		motor[1].attach(_m1, MIN_POWER, MAX_POWER);
		motor[2].attach(_m4, MIN_POWER, MAX_POWER);
		motor[3].attach(_m3, MIN_POWER, MAX_POWER);

	}

	void Calibrate(int _hard)
	{
		hardLimit = _hard;
		Serial.println("Calibrating ESC");


		Serial.print("Setting MAX: ");
		Serial.println(MAX_POWER);
		SetAll(MAX_POWER);
		
		delay(8000);

		Serial.print("Setting MIN: ");
		Serial.println(MIN_POWER);
		SetAll(MIN_POWER);
		delay(10000);

		Serial.println("ESC CALIBARATION COMPLETED!");
		motorStatus = false;

	}


	void motorAllow(bool status) 
	{


		motorStatus = status;
		if (!motorStatus)
		{
			SetAll(MIN_POWER);
		}
		else 
		{
			ESC.SetAll(Stabilize::StabIt());
		}
		digitalWrite(LED_BUILTIN, motorStatus ? HIGH : LOW);

	}


	void set(int selected, int power) 
	{
		if (!motorStatus) 
			 return;
			realpower = map(power, 0, 100, MIN_POWER, hardLimit);
		/*
		Serial.print(motor);
		Serial.print(":");
		Serial.println(realpower);
		*/
		motor[selected - 1].write(realpower);

	}

	Stabilize::Motors lastData;
	void SetAll(Stabilize::Motors _data) 
	{
		if (!motorStatus) return;
		
		if (lastData.m1 != _data.m1) 			set(1, _data.m1);
		if (lastData.m2 != _data.m2) 		set(2, _data.m2);
		if (lastData.m3 != _data.m3) 		set(3, _data.m3);
		if (lastData.m4 != _data.m4) 		set(4, _data.m4);

		lastData = _data;
	}



private:
	Servo motor[4];
	bool motorStatus = false;
	int _m1, _m2, _m3, _m4;

	int realpower;

	void SetAll(int all)
	{
		motor[0].write(all);
		motor[1].write(all);
		motor[2].write(all);
		motor[3].write(all);
	}
};

#endif

