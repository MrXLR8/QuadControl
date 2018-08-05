// F_SD.h
#include <SPI.h>
#include <SD.h>

#ifndef _F_SD_h
#define _F_SD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#pragma once
class F_SD 
{
public:
	F_SD(int chipSelectPin) 
	{
		cs = chipSelectPin;
	}

	bool start() 
	{

		if (!card.init(SPI_HALF_SPEED, cs)) 
		{
			Serial.println("[SD] Card doesn`t inserted!");
			return false;
		}
		if (!volume.init(card)) 
		{
			Serial.println("[SD] No FAT16/32 Volume found!");
			return false;
		}
		~cs;
		root.openRoot(volume);
		return true;
	}

	int MbFree() 
	{
		uint32_t volumesize;
		volumesize = volume.blocksPerCluster();
		volumesize *= volume.clusterCount();
		volumesize *= 512;
		volumesize /= 1024;
		volumesize /= 1024;
		return volumesize;
	}

private:
	int cs;

	Sd2Card card;
	SdVolume volume;
	SdFile root;
};

#endif

