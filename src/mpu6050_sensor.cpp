#include "mpu6050_sensor.h"

bool MPU6050Sensor::begin()
{
    Serial.println("Initializing MPU6050...");

    Wire.begin();

    mpu.initialize();

    initialized = mpu.testConnection();

    if (!initialized)
    {
        Serial.println("MPU6050 connection FAILED");
        return false;
    }

    Serial.println("MPU6050 connected");

    return true;
}

bool MPU6050Sensor::read(MPU6050Data &data)
{
    if (!initialized)
        return false;

    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    mpu.getMotion6(
        &ax, &ay, &az,
        &gx, &gy, &gz);

    // Accelerometer (g)
    data.accelX = ax / 16384.0f;
    data.accelY = ay / 16384.0f;
    data.accelZ = az / 16384.0f;

    // Gyroscope (deg/s)
    data.gyroX = gx / 131.0f;
    data.gyroY = gy / 131.0f;
    data.gyroZ = gz / 131.0f;

    // Library doesn't provide temperature helper
    int16_t rawTemp = mpu.getTemperature();

    data.temperature = (rawTemp / 340.0f) + 36.53f;

    return true;
}