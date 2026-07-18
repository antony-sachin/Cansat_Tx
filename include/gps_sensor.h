#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include <Arduino.h>
#include <TinyGPSPlus.h>
#include "board_config.h"

// Structure to hold one complete GPS reading
struct GPSData {
    float latitude;
    float longitude;
    float altitude;
    uint32_t satellites;
    bool isValid;
};

class GPSSensor {
public:
    GPSSensor();
    bool begin();
    bool read(GPSData &data);

private:
    TinyGPSPlus gps;
    HardwareSerial gpsSerial;
};

#endif