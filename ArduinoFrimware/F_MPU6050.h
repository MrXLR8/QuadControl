// F_MPU6050.h
#include "MPU6050.h"


#ifndef _F_MPU6050_h
#define _F_MPU6050_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#pragma once


struct xyz 
{
	int x, y, z;
};

enum coords {X,Y,Z};

class F_MPU6050
{
public:
	~F_MPU6050()
	{

	};

	F_MPU6050() 
	{

	}


	bool start() 
	{
		accel.initialize();

		accel.setXAccelOffset(-2959);
		accel.setYAccelOffset(1315);
		accel.setZAccelOffset(1558);

		accel.setXGyroOffset(66);
		accel.setYGyroOffset(-49);
		accel.setZGyroOffset(25);

		return accel.testConnection();
	}

	void setOffsets(xyz accelOffsets, xyz gyroOffsets) 
	{
		accel.setXAccelOffset(accelOffsets.x);
		accel.setYAccelOffset(accelOffsets.y);
		accel.setZAccelOffset(accelOffsets.z);

		accel.setXGyroOffset(gyroOffsets.x);
		accel.setYGyroOffset(-gyroOffsets.y);
		accel.setZGyroOffset(gyroOffsets.z);
	}

	xyz getAccelXYZ() 
	{
		update();
		AccResult.x= ((180 / 3.141592) * atan(ax_raw / sqrt(square(ay_raw) + square(az_raw))));
		AccResult.y= ((180 / 3.141592) * atan(ay_raw / sqrt(square(ax_raw) + square(az_raw))));
		AccResult.z= ((180 / 3.141592) * atan(sqrt(square(ay_raw) + square(ax_raw)) / az_raw));
		return AccResult;
	}

	xyz getGyroXYZ()
	{
		update();
		GyroResult.x = gx_raw / 250;
		GyroResult.y = gy_raw / 250;
		GyroResult.z = gz_raw / 250;
		return GyroResult;
	}

	int get(coords axis) 
	{
		update();
		switch (axis) 
		{
		case X:
			return AccResult.x;
			break;
		case Y:
			return AccResult.y;
			break;
		case Z:
			return AccResult.z;
			break;
		}
	}
	


private:
	
	void update() 
	{
		accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
	}

	MPU6050 accel;
	int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
	xyz AccResult,GyroResult;
};

#endif

