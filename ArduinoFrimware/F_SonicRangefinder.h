// F_SonicRangefinder.h

#ifndef _F_SONICRANGEFINDER_h
#define _F_SONICRANGEFINDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



class F_SonicRangefinder
{



 public:
	
	 F_SonicRangefinder(int trigger,int echo) 
	 {
		 pinMode(trigger, OUTPUT);
		 pinMode(echo, INPUT);
		 trigPin = trigger;
		 echoPin = echo;
	 }

	 int getCM() 
	 {
		 int duration, distance;
		 // для большей точности установим значение LOW на пине Trig
		 digitalWrite(trigPin, LOW);
		 delayMicroseconds(2);
		 // Теперь установим высокий уровень на пине Trig
		 digitalWrite(trigPin, HIGH);
		 // Подождем 10 μs 
		 delayMicroseconds(10);
		 digitalWrite(trigPin, LOW);
		 // Узнаем длительность высокого сигнала на пине Echo
		 duration = pulseIn(echoPin, HIGH);
		 // Рассчитаем расстояние
		 distance = duration / 58;
		 // Выведем значение в Serial Monitor
		 return distance;
	 }

	 int getInch() 
	 {
		 int duration, distance;
		 // для большей точности установим значение LOW на пине Trig
		 digitalWrite(trigPin, LOW);
		 delayMicroseconds(2);
		 // Теперь установим высокий уровень на пине Trig
		 digitalWrite(trigPin, HIGH);
		 // Подождем 10 μs 
		 delayMicroseconds(10);
		 digitalWrite(trigPin, LOW);
		 // Узнаем длительность высокого сигнала на пине Echo
		 duration = pulseIn(echoPin, HIGH);
		 // Рассчитаем расстояние
		 distance = duration / 58;
		 // Выведем значение в Serial Monitor
		 return distance*0.39;
	 }

private:

	int trigPin;
	int echoPin;

};


#endif

