#include "gps_sensor.h"

// Initialize HardwareSerial using UART 2
GPSSensor::GPSSensor() : gpsSerial(2) {}

bool GPSSensor::begin() {
    Serial.println("Initializing GPS...");

    // The NEO-7M default baud rate is typically 9600.
    // Using standard 8N1 serial configuration mapping to your custom pins.
    gpsSerial.begin(9600, SERIAL_8N1, GPS_UART_RX, GPS_UART_TX);
    
    // Wait briefly to ensure the serial port stabilizes
    delay(100);

    Serial.println("GPS initialized.");
    return true; 
}

bool GPSSensor::read(GPSData &data) {
    // Feed the TinyGPSPlus object with any available serial data
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    // A location is only useful if it's both valid and recently updated
    data.isValid = gps.location.isValid() && gps.location.isUpdated();

    // Populate coordinates
    if (gps.location.isValid()) {
        data.latitude = gps.location.lat();
        data.longitude = gps.location.lng();
    } else {
        data.latitude = 0.0;
        data.longitude = 0.0;
    }

    // Populate altitude
    if (gps.altitude.isValid()) {
        data.altitude = gps.altitude.meters();
    } else {
        data.altitude = 0.0;
    }

    // Populate satellite count (useful for diagnosing a bad lock)
    if (gps.satellites.isValid()) {
        data.satellites = gps.satellites.value();
    } else {
        data.satellites = 0;
    }

    return data.isValid;
}