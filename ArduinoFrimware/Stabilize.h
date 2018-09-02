// Stabilize.h

#ifndef _STABILIZE_h
#define _STABILIZE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <MPU6050_tockn.h>


class Stabilize 
{
public:
	static MPU6050* gyro;

	class Angle
	{
	public:
		int pitch;
		int roll;
		friend const Angle operator+(const Angle& left, const Angle& right)
		{
			Angle result;
			result.pitch = left.pitch + right.pitch;
			result.roll = left.roll + right.roll;
			return result;
		}

		friend const Angle operator-(const Angle& left, const Angle& right)
		{
			Angle result;
			result.pitch = left.pitch - right.pitch;
			result.roll = left.roll - right.roll;
			return result;
		}

		friend const Angle operator+=(Angle& left, const Angle& right)
		{
			left.pitch += right.pitch;
			left.roll += right.roll;
			return left;
		}

		friend const Angle operator-=(Angle& left, const Angle& right)
		{
			left.pitch -= right.pitch;
			left.roll -= right.roll;
			return left;
		}

		friend bool operator==(const Angle& left, const Angle& right) 
		{
			if (left.pitch == right.pitch)
				if (left.roll == right.roll)
					return true;
			return false;
		}

		Angle(int _pitch, int _roll) 
		{
			pitch = _pitch;
			roll = _roll;
		}
		Angle() {}
	};

	class Motors 
	{
	public:
		int m1, m2, m3, m4;
		Motors() 
		{
			m1 = middlePower;
			m2 = middlePower;
			m3 = middlePower;
			m4 = middlePower;
		}
		Motors(int _m1, int _m2, int _m3, int _m4) 
		{
			m1 = _m1;
			m2 = _m2;
			m3 = _m3;
			m4 = _m4;
		}
	
		static Motors calculateMiddle(Motors first,Motors second) 
		{
			return Motors((first.m1 + second.m1) / 2, (first.m2 + second.m2) / 2, (first.m3 + second.m3) / 2, (first.m4 + second.m4) / 2);
		}

		friend bool operator==(const Motors& left, const Motors& right)
		{
			if (left.m1 == right.m1)
				if (left.m2 == right.m2)
					if (left.m3 == right.m3)
						if (left.m4 == right.m4)
					return true;
			return false;
		}

	};

	

	static Angle stableVector; //неподвижная позиция
	static Angle currentVector; // что сейчас на гиро
	static Angle requiredVector;// что должно быть

	static Motors last;
	static const int sensivity = 1;
	static int middlePower;

	static void start() 
	{



		stableVector.pitch = 0;
		stableVector.roll = 0;

		middlePower = 50;

		requiredVector = stableVector;
		getCurrent();
	}
	Stabilize()
	{


	}


	static Motors StabIt()
	{
		//roll.m1 = map(diff, -90+(requiredVector.roll*-1), 90 + (requiredVector.roll*-1), 0, 100); //TODO: при проблемах убрать запару у 90

		int diff;
		Motors roll= Motors();
		Motors pitch = Motors();
		//roll
		getCurrent();
		diff = requiredVector.roll - currentVector.roll; //0-10=-10
		
	


		roll.m1 = map(diff*-1, -90/ sensivity, 90/ sensivity,  middlePower-50, 50+ middlePower); // дифф -10. но левая сторона должна подниматься при падении. значит диф меняем
		roll.m3 = roll.m1;

		roll.m2= map(diff, -90/ sensivity, 90/ sensivity, 0+ middlePower - 50, 50+ middlePower); // дифф -10. ослабляем эту сторону. Возможно надо ослабить эффект каждого на пополам?
		roll.m4= roll.m2;
		//pitch
		diff = requiredVector.pitch - currentVector.pitch;
		pitch.m1 = map(diff*-1, -90/ sensivity, 90/ sensivity, 0+ middlePower - 50, 50+ middlePower);
		pitch.m2 = pitch.m1;
		
		pitch.m3 = map(diff, -90/ sensivity, 90/ sensivity, 0+ middlePower - 50, 50+ middlePower);
		pitch.m4 = pitch.m3;
		
		 

		return Motors::calculateMiddle(pitch, roll);

	}

	static Stabilize::Angle getAccel()
	{
		return Stabilize::Angle(gyro->getAngleY(), gyro->getAngleX()*-1);
	}
	private:

		static void getCurrent()
		{
			Angle accel= getAccel();
			currentVector.pitch = int(accel.pitch);
			currentVector.roll = int(accel.roll);
		}

	

};

#endif

