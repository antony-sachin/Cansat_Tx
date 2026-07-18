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

    // Convert acceleration from m/s² to g
    data.accelX = accel.acceleration.x / 9.80665f;
    data.accelY = accel.acceleration.y / 9.80665f;
    data.accelZ = accel.acceleration.z / 9.80665f;

    // Convert angular velocity from rad/s to deg/s
    data.gyroX = gyro.gyro.x * 180.0f / PI;
    data.gyroY = gyro.gyro.y * 180.0f / PI;
    data.gyroZ = gyro.gyro.z * 180.0f / PI;

    data.temperature = temp.temperature;

    return true;
}