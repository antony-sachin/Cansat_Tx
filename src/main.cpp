#include <Arduino.h>
#include <Wire.h>
#include "board_config.h"
#include "bme680_sensor.h"
#include "mpu6050_sensor.h"
#include "gps_sensor.h"
#include "pms5003_sensor.h" // <--- ADD THIS
#include "sx1278_lora.h"

BME680Sensor bme;
MPU6050Sensor imu;
GPSSensor myGps;
PMS5003Sensor pms;          // <--- ADD THIS
SX1278LoRa lora;

BME680Data env;
MPU6050Data motion;
GPSData loc;
PMS5003Data dust;           // <--- ADD THIS

unsigned long packetCount = 0; 

void setup() {
    Serial.begin(115200);
    delay(1000);
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    
    imu.begin();
    bme.begin();
    myGps.begin();
    pms.begin();            // <--- ADD THIS
    
    LoRaConfig config; 
    lora.begin(config);
}

void loop() {
    // Read all sensors
    bool bmeValid = bme.read(env);
    bool imuValid = imu.read(motion);
    bool gpsValid = myGps.read(loc);
    bool pmsValid = pms.read(dust);   // <--- ADD THIS

    // Expand buffer size to handle the extra variables safely
    char payloadBuffer[256]; 

    // Format the entire telemetry string 
    snprintf(payloadBuffer, sizeof(payloadBuffer), 
             "%lu,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.6f,%.6f,%.1f,%u,%u,%u",
             packetCount,
             bmeValid ? env.temperature : 0.0, 
             bmeValid ? env.pressure : 0.0, 
             bmeValid ? env.altitude : 0.0,
             imuValid ? motion.accelX : 0.0, 
             imuValid ? motion.accelY : 0.0, 
             imuValid ? motion.accelZ : 0.0,
             gpsValid ? loc.latitude : 0.0,      
             gpsValid ? loc.longitude : 0.0,     
             gpsValid ? loc.altitude : 0.0,
             pmsValid ? dust.pm1_0 : 0,          // <--- ADD THIS
             pmsValid ? dust.pm2_5 : 0,          // <--- ADD THIS
             pmsValid ? dust.pm10_0 : 0);        // <--- ADD THIS

    Serial.print("Transmitting: ");
    Serial.println(payloadBuffer);

    LoRaStatus status = lora.send(payloadBuffer);
    
    if (status == LoRaStatus::OK) {
        packetCount++;
    }

    delay(1000);
}