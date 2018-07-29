
MPU6050 accel;
int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;

int arx;
int ary;
int arz;


void AccelSetup()
{

	accel.initialize();

	accel.setXAccelOffset(-3045);
	accel.setYAccelOffset(1265);
	accel.setZAccelOffset(1571);

	accel.setXGyroOffset(66);
	accel.setYGyroOffset(-50);
	accel.setZGyroOffset(28);

	Serial.println(accel.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

int getAccelX() 
{
	accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
	
	return ((180 / 3.141592) * atan(ax_raw / sqrt(square(ay_raw) + square(az_raw))));
}

int getAccelY()
{
	accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
	return ((180 / 3.141592) * atan(ay_raw / sqrt(square(ax_raw) + square(az_raw))));
}

int getAccelZ()
{
	accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
	return ((180 / 3.141592) * atan(sqrt(square(ay_raw) + square(ax_raw)) / az_raw));
}


