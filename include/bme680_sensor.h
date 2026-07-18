#ifndef BME680_SENSOR_H
#define BME680_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME680.h>

// Structure to hold one complete sensor reading
struct BME680Data
{
    float temperature;   // °C
    float humidity;      // %
    float pressure;      // hPa
    float gasResistance; // KΩ
    float altitude;      // meters
};

class BME680Sensor
{
public:

    // Initialize sensor
    bool begin();

    // Read all sensor values
    bool read(BME680Data &data);

private:

    Adafruit_BME680 bme;
};

#endif