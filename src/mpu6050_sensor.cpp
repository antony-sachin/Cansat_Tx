#include "mpu6050_sensor.h"

bool MPU6050Sensor::begin()
{
    if (!mpu.begin())
    {
        return false;
    }

    // Accelerometer range
    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);

    // Gyroscope range
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    // Low pass filter
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    return true;
}

bool MPU6050Sensor::read(MPU6050Data &data)
{
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    mpu.getEvent(&accel, &gyro, &temp);

    data.accelX = accel.acceleration.x;
    data.accelY = accel.acceleration.y;
    data.accelZ = accel.acceleration.z;

    data.gyroX = gyro.gyro.x;
    data.gyroY = gyro.gyro.y;
    data.gyroZ = gyro.gyro.z;

    data.temperature = temp.temperature;

    return true;
}