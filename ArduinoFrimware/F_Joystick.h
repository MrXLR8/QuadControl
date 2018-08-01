// F_Joystick.h

#ifndef _F_JOYSTICK_h
#define _F_JOYSTICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once

struct Vector2D
{
	int x;
	int y;
};
class F_Joystick
{
public:
	~F_Joystick() 
	{
		pressPin = 0;
	};

	F_Joystick(int _xPin, int _yPin)
	{
		xPin = _xPin;
		yPin = _yPin;
	}
	F_Joystick(int _xPin, int _yPin,int _pressPin, bool resistor)
	{
		xPin = _xPin;
		yPin = _yPin;

		pressPin = _pressPin;
		if (resistor) {
			pinMode(pressPin, INPUT_PULLUP);
		}
		else
		{
			pinMode(pressPin, INPUT);
		}
	}
	

	Vector2D position()
	{
		pos.x = analogRead(xPin);
		pos.y = analogRead(yPin);
		return pos;
	}

	bool pressed() 
	{
		if(pressPin!=0) 
			if (digitalRead(pressPin) == LOW)
				return true;

		return false;
	}


private:
	int xPosition = 0;
	int yPosition = 0;

	int xPin;
	int yPin;
	int pressPin = 0;
	Vector2D pos;
};



#endif

