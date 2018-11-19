// WiFiTimingFilter.h

#ifndef _WIFITIMINGFILTER_h
#define _WIFITIMINGFILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <StandardCplusplus.h>
#include <queue>

#include "TimePassed.h"

using namespace std;

class WiFiTimingFilter 
{
public:
	queue<String> content;

	TimePassed ochered;

	WiFiTimingFilter() 
	{
		max = 0;
		counter = 0;
		
	}
	int counter;
	int max;

	const int delay = 20;


	void addString(String str) 
	{

		if (content.size() > 20) 
		{
			content.pop();
			
		}
		content.push(str);

	}
	void removeLastString() 
	{
		content.pop();

	}

	void proceed() 
	{
			if (!content.empty())
			{

				if (ochered.passed(delay))
				{
					Serial.println(content.front());
					content.pop();
				}
			}


	}
};
#endif

