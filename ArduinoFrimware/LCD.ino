#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);


void DisplaySetup() 
{
	lcd.init();
	lcd.backlight();
}

void DisplayFirstText() 
{
	lcd.print("GYROSCOPE:");
	lcd.setCursor(0, 2);
	lcd.print("ACCELOMETER:");
}

void DisplayPrintXYZ(int rad, int x, int y, int z)
{
	int lenght = 0;

	lcd.setCursor(0, rad);

	String xS = String(x) + "|";
	lcd.print(xS);
	lenght += xS.length();
	lcd.setCursor(lenght, rad);

	String yS = String(y) + "|";
	lcd.print(yS);
	lenght += yS.length();
	lcd.setCursor(lenght, rad);
		
	String zS = String(z) + "|";
	lcd.print(zS);
}

void DisplayPrintXY(int rad, int x, int y)
{
	int lenght = 0;

	lcd.setCursor(0, rad);

	String xS = String(x) + "|";
	lcd.print(xS);
	lenght += xS.length();
	lcd.setCursor(lenght, rad);

	String yS = String(y) + "|";
	lcd.print(yS);

}

void DisplayPrint(int rad, String text, int x)
{
	int lenght = 0;

	lcd.setCursor(0, rad);
	lcd.print(text + ": ");
	lenght = text.length() + 2;

	lcd.setCursor(lenght, rad);
	lcd.print(x);

}

void DisplayClear() 
{
	lcd.clear();
}