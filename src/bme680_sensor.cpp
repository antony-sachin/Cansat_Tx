#include "bme680_sensor.h"

bool BME680Sensor::begin()
{
    // Try both possible I2C addresses
    if (!bme.begin(0x76))
    {
        if (!bme.begin(0x77))
        {
            return false;
        }
    }

    // Oversampling configuration
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);

    // Gas heater configuration
    bme.setGasHeater(320, 150);

    return true;
}

bool BME680Sensor::read(BME680Data &data)
{
    // Perform one complete measurement
    if (!bme.performReading())
    {
        return false;
    }

    data.temperature = bme.temperature;
    data.humidity = bme.humidity;

    // Convert Pa -> hPa
    data.pressure = bme.pressure / 100.0f;

    // Convert Ohms -> Kilo Ohms
    data.gasResistance = bme.gas_resistance / 1000.0f;

    // Sea level pressure = 1013.25 hPa
    data.altitude = bme.readAltitude(1013.25);

    return true;
}