// F_LCD.h
#include <LiquidCrystal_I2C.h>

#ifndef _F_LCD_h
#define _F_LCD_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#pragma once


class F_LCD
{
public:
	~F_LCD()
	{

	};

	F_LCD(int sizex, int sizey) 
	{

			disp = new LiquidCrystal_I2C(0x27, sizex, sizey);
			_sizeX = sizex;

	}


	F_LCD(int adress,int sizex, int sizey)
	{
		disp = new LiquidCrystal_I2C(adress, sizex, sizey);
		_sizeX = sizex;
	}

	void start() 
	{
		disp->init();
		disp->backlight();
		disp->clear();
	}

	void clear() 
	{
		disp->clear();
	}

	void printValues(int ryad, int values[], int count)
	{
		disp->setCursor(0, ryad);
		String printable;
		int lenght;

		for (int i = 0; i < count; i++) 
		{
			printable = String(values[i]) + "|";
			lenght += printable.length();
			if (lenght > _sizeX) return;
			disp->print(printable);
			disp->setCursor(lenght, ryad);
		}
	}

	void printValue(int ryad, String text, int value)
	{
		int lenght = 0;

		disp->setCursor(0, ryad);
		disp->print(text + ": ");
		lenght = text.length() + 2;

		disp->setCursor(lenght, ryad);
		disp->print(value);
	}

	void printText(int ryad, int position,String Text)
	{
		int lenght = Text.length();
		int outborders = (position + lenght)-_sizeX;
		Serial.println(outborders);
		if (outborders > 0) { position -= outborders; }
		disp->setCursor(position, ryad);
		disp->print(Text);
		
	}


private:
	int _sizeX = 0;
	LiquidCrystal_I2C *disp = nullptr;
};

#endif

