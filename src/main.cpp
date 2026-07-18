#include <Arduino.h>
#include <Wire.h>

#include "board_config.h"
#include "bme680_sensor.h"
#include "mpu6050_sensor.h"

BME680Sensor bme;
MPU6050Sensor imu;

BME680Data env;
MPU6050Data motion;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    Serial.println("===============================");
    Serial.println();

    if (imu.begin())
    {
        Serial.println("MPU6050 initialized.");
    }
    else
    {
        Serial.println("MPU6050 initialization FAILED!");
    }

    if (bme.begin())
    {
        Serial.println("BME680 initialized.");
    }
    else
    {
        Serial.println("BME680 initialization FAILED!");
    }
}

void loop()
{
    if (bme.read(env))
    {
        Serial.println("====== BME680 ======");

        Serial.print("Temperature : ");
        Serial.print(env.temperature);
        Serial.println(" C");

        Serial.print("Humidity    : ");
        Serial.print(env.humidity);
        Serial.println(" %");

        Serial.print("Pressure    : ");
        Serial.print(env.pressure);
        Serial.println(" hPa");

        Serial.print("Gas         : ");
        Serial.print(env.gasResistance);
        Serial.println(" kOhm");

        Serial.print("Altitude    : ");
        Serial.print(env.altitude);
        Serial.println(" m");
    }
    else
    {
        Serial.println("BME680 not initialized.");
    }

    if (imu.read(motion))
    {
        Serial.println("====== MPU6050 ======");

        Serial.print("Accel X : ");
        Serial.println(motion.accelX);

        Serial.print("Accel Y : ");
        Serial.println(motion.accelY);

        Serial.print("Accel Z : ");
        Serial.println(motion.accelZ);

        Serial.print("Gyro X : ");
        Serial.println(motion.gyroX);

        Serial.print("Gyro Y : ");
        Serial.println(motion.gyroY);

        Serial.print("Gyro Z : ");
        Serial.println(motion.gyroZ);

        Serial.print("Temperature : ");
        Serial.print(motion.temperature);
        Serial.println(" C");
    }
    else
    {
        Serial.println("MPU6050 not initialized.");
    }

    Serial.println();

    delay(1000);
}