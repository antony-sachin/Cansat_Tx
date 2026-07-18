#ifndef MPU6050_SENSOR_H
#define MPU6050_SENSOR_H

#include <Arduino.h>
#include <Wire.h>

#include <I2Cdev.h>
#include <MPU6050.h>

struct MPU6050Data
{
    float accelX;
    float accelY;
    float accelZ;

    float gyroX;
    float gyroY;
    float gyroZ;

    float temperature;
};

class MPU6050Sensor
{
public:
    bool begin();
    bool read(MPU6050Data &data);

private:
    MPU6050 mpu;
    bool initialized = false;
};

#endif