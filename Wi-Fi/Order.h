// Order.h

#ifndef _ORDER_h
#define _ORDER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <vector>
#include "SoftwareSerial.h"

using namespace std;
#pragma once


// PING 1 req 2 resp
class Order
{
public:
	String type;
	vector<String> content;

	static SoftwareSerial* wifi;
	

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
		if (content.empty()) return;

		if (type == "WP")
		{
			if (content[0] == "1")
			{
				wifi->write("[WP]2");

			}
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
			{      // "—" сплиттер
				buffer += line[i];
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

