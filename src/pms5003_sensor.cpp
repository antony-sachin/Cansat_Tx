#include "pms5003_sensor.h"

// Initialize HardwareSerial using UART 1, and pass it to the PMS library
PMS5003Sensor::PMS5003Sensor() : pmsSerial(1), pms(pmsSerial) {}

bool PMS5003Sensor::begin() {
    // PMS5003 operates at 9600 baud standard
    pmsSerial.begin(9600, SERIAL_8N1, PMS_UART_RX, PMS_UART_TX);
    
    delay(100); // Allow time for UART to stabilize

    // Set passive mode so it only reports data when we ask for it
    pms.passiveMode(); 
    
    return true; 
}

bool PMS5003Sensor::read(PMS5003Data &data) {
    PMS::DATA pmsRawData;
    
    // Request a reading from the sensor
    pms.requestRead();
    
    // Attempt to read the packet with a brief 200ms timeout
    if (pms.readUntil(pmsRawData, 200)) {
        // We use the Atmospheric Environment (AE) standard values
        data.pm1_0 = pmsRawData.PM_AE_UG_1_0;
        data.pm2_5 = pmsRawData.PM_AE_UG_2_5;
        data.pm10_0 = pmsRawData.PM_AE_UG_10_0;
        data.isValid = true;
        return true;
    } else {
        data.isValid = false;
        return false;
    }
}