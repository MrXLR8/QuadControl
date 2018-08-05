/*

VCC - 5V
CS (constructor (def-4))
MOSI 11
MISO 12
SCK 13

*/
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

		if (!SD.begin(cs)) 
		{
			Serial.println("[SD] Card doesn`t inserted!");
			return false;
		}
		~cs;
		return true;
	}


	String ReadFile(String filename)  // для записи в папки использовать такие же скобки как в комментах
	{
		File file = SD.open(filename, FILE_READ);
		String result;
		if (file) 
		{
			while (file.available()) 
			{
				result +=(char) file.read();
			}
			file.close();
			return result;
		}
		else { Serial.println("[SD] Failed to open file to read!"); return ""; }
	}

	bool WriteFile(String filename, String textToWrite) 
	{
		
		File file = SD.open(filename,FILE_WRITE);
		if (file) 
		{
			file.println(textToWrite);
			file.close();
			return true;
		}
		else 
		{
			Serial.println("[SD] Failed to open file to write!"); 
			return false;
		}
	}

	bool CreateDir(String dirname) 
	{
		return SD.mkdir(dirname);
	}

	bool RemoveFile(String filename) 
	{
		return SD.remove(filename);
	}

	bool RemoveDir(String dirname) 
	{
		return SD.rmdir(dirname);
	}

	/*
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
	*/
private:
	int cs;


};

#endif

