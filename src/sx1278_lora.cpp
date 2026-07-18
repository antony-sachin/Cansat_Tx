#include "sx1278_lora.h"

// Constructor: Initialize the module with pins from board_config.h
// RADIOLIB_NC is used for DIO1 since it is not defined/needed for basic LoRa
SX1278LoRa::SX1278LoRa() 
    : module(LORA_CS_PIN, LORA_DIO0_PIN, LORA_RST_PIN, RADIOLIB_NC), 
      radio(&module) {
    rssi = 0;
    snr = 0;
    frequencyError = 0;
}

bool SX1278LoRa::begin(const LoRaConfig &config) {
    Serial.println("Initializing LoRa...");

    // Optional: Explicitly begin the SPI bus with your custom pins
    SPI.begin(LORA_SCK_PIN, LORA_MISO_PIN, LORA_MOSI_PIN, LORA_CS_PIN);

    // Initialize the radio with the configuration struct
    int state = radio.begin(config.frequency,
                            config.bandwidth,
                            config.spreadingFactor,
                            config.codingRate,
                            config.syncWord,
                            config.txPower,
                            config.preambleLength,
                            0); // 0 = default gain

    if (state != RADIOLIB_ERR_NONE) {
        Serial.print("LoRa Init failed, code: ");
        Serial.println(state);
        return false;
    }

    if (config.crc) {
        radio.setCRC(true);
    }

    Serial.println("LoRa initialized.");
    return true;
}

LoRaStatus SX1278LoRa::send(const String &message) {
    // Pass the payload as a const char* instead of a const String reference
    int state = radio.transmit(message.c_str());

    if (state == RADIOLIB_ERR_NONE) {
        return LoRaStatus::OK;
    } else {
        Serial.print("LoRa TX failed, code: ");
        Serial.println(state);
        return LoRaStatus::TX_FAILED;
    }
}

LoRaStatus SX1278LoRa::receive(String &message) {
    int state = radio.receive(message);

    if (state == RADIOLIB_ERR_NONE) {
        // Save the transmission stats
        rssi = radio.getRSSI();
        snr = radio.getSNR();
        frequencyError = radio.getFrequencyError();
        return LoRaStatus::OK;
    } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
        return LoRaStatus::NO_PACKET;
    } else {
        return LoRaStatus::RX_FAILED;
    }
}

void SX1278LoRa::sleep() {
    radio.sleep();
}

void SX1278LoRa::standby() {
    radio.standby();
}

float SX1278LoRa::getRSSI() const {
    return rssi;
}

float SX1278LoRa::getSNR() const {
    return snr;
}

float SX1278LoRa::getFrequencyError() const {
    return frequencyError;
}