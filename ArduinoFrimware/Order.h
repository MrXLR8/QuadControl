// Order.h

#ifndef _ORDER_h
#define _ORDER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <StandardCplusplus.h>
#include <vector>

#include "Stabilize.h"
#include "F_ESC.h"
using namespace std;
#pragma once


//WP - PING 1 req 2 resp
class Order
{
public:
	String type;
	vector<String> content;
	static F_ESC* ESC;
	static MPU6050* mpu6050;


	Order() {}

	Order(String _type, vector<String> _content)
	{
		
		type = _type;

		content = _content;

	}

	void Parse(String str)
	{
		String body;
		if (str[0] == '['&str[3] == ']')
		{
			type = "";
			type += str[1];
			type += str[2];

			type = type;

			body = (split(str, ']'))[1];

			content = split(body, '.');

		}

	}

	String ToString()
	{
		String result = "[" + type + "]";
		for (String s : content)
		{
			result += s;
			result += ".";
		}
		result.remove(result.length() - 1);
		return result;
	}

	void Execute()
	{
		//Serial.println(this->ToString());


		if (content.empty()) return;
		
		if (type == "WP") //PING
		{

			
			if (content[0] == "1")
			{
			
				content[0] = "2";
				Serial.println(this->ToString());
				
				content[0] = "1";
			}
		}
	
		if (type == "GR")  //PING запрос на данные гиро
		{
			if (content[0] == "1")
			{
				Stabilize::Angle toSendA;
				toSendA = Stabilize::getAccel();
				String _pitch = String(int(toSendA.pitch));
				String _roll = String(int(toSendA.roll));
				String toSend = "[GD]" + _pitch + "." + _roll;
				Serial.println(toSend);
			}
		}
	
		if (type == "AC")  //“ребуемый вектор и т€га 
		{
			Stabilize::Angle recived;
			recived.pitch = atoi(content[0].c_str());
			recived.roll = atoi(content[1].c_str());
			Stabilize::requiredVector = Stabilize::stableVector + recived;
			Stabilize::middlePower = atoi(content[2].c_str());
			ESC->overRideLastCheck = true;
		}

		if (type == "CA")  //калибровка гиро
		{
			mpu6050->calcGyroOffsets(true);
			delay(2000);
		}

		if (type == "MA") //питание моторов
		{
			bool what = atoi(content[0].c_str());
			ESC->motorAllow(what);
			ESC->overRideLastCheck = true;

		}
		if (type == "MP") //принудительное включение мотора
		{
			int motor = atoi(content[0].c_str());
			int power = atoi(content[1].c_str());
			ESC->overRideLastCheck = true;
			ESC->set(motor, power);

		}
	}


	~Order()
	{

	}

private:

	vector<String> split(String line, char delimer)
	{
		String buffer;
		vector<String> commands;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] != delimer)
			{    
				if (line[i] != '\n') 
				{// "Ч" сплиттер
					if (line[i] != '\r') 
					{
						buffer += line[i];
					}
				}
			}
			else
			{
				commands.push_back(buffer);
				buffer = "";
			}
		}
		if (buffer != "") commands.push_back(buffer);
		return commands;
	}
};




#endif

