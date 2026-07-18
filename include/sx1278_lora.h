#ifndef SX1278_LORA_H
#define SX1278_LORA_H

#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>
#include "board_config.h"

// Structure holding LoRa configuration.
struct LoRaConfig {
    float frequency = 433.0;     // MHz
    float bandwidth = 125.0;     // kHz
    uint8_t spreadingFactor = 8;
    uint8_t codingRate = 5;      // 5 => 4/5
    uint8_t syncWord = 0x12;
    int8_t txPower = 17;         // dBm
    uint16_t preambleLength = 8;
    bool crc = true;
};

// Driver return values.
enum class LoRaStatus {
    OK,
    INIT_FAILED,
    TX_FAILED,
    RX_FAILED,
    NO_PACKET
};

class SX1278LoRa {
public:
    SX1278LoRa();
    bool begin(const LoRaConfig &config = LoRaConfig());
    LoRaStatus send(const String &message);
    LoRaStatus receive(String &message);
    void sleep();
    void standby();
    float getRSSI() const;
    float getSNR() const;
    float getFrequencyError() const;

private:
    Module module;
    SX1278 radio;
    float rssi;
    float snr;
    float frequencyError;
};

#endif