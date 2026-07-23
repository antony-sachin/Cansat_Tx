#include <Arduino.h>
#include <Wire.h>
#include "board_config.h"
#include "bme680_sensor.h"
#include "mpu6050_sensor.h"
#include "gps_sensor.h"
#include "pms5003_sensor.h" 
#include "sx1278_lora.h"

BME680Sensor bme;
MPU6050Sensor imu;
GPSSensor myGps;
PMS5003Sensor pms;          
SX1278LoRa lora;

BME680Data env;
MPU6050Data motion;
GPSData loc;
PMS5003Data dust;           

unsigned long packetCount = 0; 

void setup() {
    Serial.begin(115200);
    delay(1000);
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    
    imu.begin();
    bme.begin();
    myGps.begin();
    pms.begin();            
    
    LoRaConfig config; 
    lora.begin(config);
    Serial.println(config.frequency);
    Serial.println(config.bandwidth);
    Serial.println(config.spreadingFactor);
    Serial.println(config.codingRate);
    Serial.println(config.syncWord);
    Serial.println(config.preambleLength);
    Serial.println(config.crc);
}

unsigned long lastTxTime = 0;
const unsigned long TX_INTERVAL = 1000; // Transmit every 1000 milliseconds

void loop() {
    // 1. Constantly feed the GPS object to prevent buffer overflows
    // This runs thousands of times a second
    bool gpsValid = myGps.read(loc); 

    // 2. Check if 1 second has passed
    if (millis() - lastTxTime >= TX_INTERVAL) {
        // Reset the timer
        lastTxTime = millis(); 
        
        // Read the other sensors only when we are ready to transmit
        bool bmeValid = bme.read(env);
        bool imuValid = imu.read(motion);
        bool pmsValid = pms.read(dust);   

        char payloadBuffer[256]; 

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
                 pmsValid ? dust.pm1_0 : 0,          
                 pmsValid ? dust.pm2_5 : 0,          
                 pmsValid ? dust.pm10_0 : 0);        

        Serial.print("Transmitting: ");
        Serial.println(payloadBuffer);

        LoRaStatus status = lora.send(payloadBuffer);
        
        if (status == LoRaStatus::OK) {
            packetCount++;
        }
        Serial.println();
    }
}