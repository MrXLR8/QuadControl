// TimePassed.h

#ifndef _TIMEPASSED_h
#define _TIMEPASSED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class TimePassed
{
public:
	TimePassed() 
	{
	}

	int lastmills = 0;
	bool passed(int delay) 
	{
		int diff = millis() - lastmills;

		if (diff >= delay)
		{
			lastmills = millis();
			return true;
		}
		return false;
	}

};

#endif

;;;;;;;;;;;;;;;;;;;;;
