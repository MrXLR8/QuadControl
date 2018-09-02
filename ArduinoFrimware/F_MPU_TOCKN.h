// F_MPU_TOCKN.h

#ifndef _F_MPU_TOCKN_h
#define _F_MPU_TOCKN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <MPU6050_tockn.h>
//класс для инвертации питча с ролом изза плохой конструкции дрона :С
class F_MPU_TOCKN 
{
	static MPU6050* mpu6050;

	static void update() 
	{

	}
 };

#endif

