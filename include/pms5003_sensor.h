#ifndef PMS5003_SENSOR_H
#define PMS5003_SENSOR_H

#include <Arduino.h>
#include <PMS.h>
#include "board_config.h"

// Structure to hold one complete PMS5003 reading
struct PMS5003Data {
    uint16_t pm1_0;
    uint16_t pm2_5;
    uint16_t pm10_0;
    bool isValid;
};

class PMS5003Sensor {
public:
    PMS5003Sensor();
    bool begin();
    bool read(PMS5003Data &data);

private:
    HardwareSerial pmsSerial;
    PMS pms;
};

#endif