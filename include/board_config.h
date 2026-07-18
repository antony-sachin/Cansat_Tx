#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

/*=========================================================
                    I2C BUS
=========================================================*/

#define I2C_SDA_PIN        21
#define I2C_SCL_PIN        22

/*=========================================================
                  PMS5003 UART
=========================================================*/

#define PMS_UART_RX        16      // ESP32 RX <- PMS5003 TX
#define PMS_UART_TX        17      // ESP32 TX -> PMS5003 RX

/*=========================================================
                  GPS UART
=========================================================*/

#define GPS_UART_RX        32      // ESP32 RX <- NEO-7M TX
#define GPS_UART_TX        33      // ESP32 TX -> NEO-7M RX

/*=========================================================
                    LORA (SX1278)
=========================================================*/

#define LORA_SCK_PIN       18
#define LORA_MISO_PIN      19
#define LORA_MOSI_PIN      23

#define LORA_CS_PIN        5
#define LORA_RST_PIN       27
#define LORA_DIO0_PIN      26

/*=========================================================
                    MQ SENSOR
=========================================================*/

#define MQ_ANALOG_PIN      34

#endif