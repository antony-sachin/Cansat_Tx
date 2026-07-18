# Changes required in Adafruit_BME680.cpp to allow 3rd party MPU6050


# Current code
```cpp
Adafruit_BusIO_Register chip_id =
    Adafruit_BusIO_Register(i2c_dev, MPU6050_WHO_AM_I, 1);

// make sure we're talking to the right chip
if (chip_id.read() != MPU6050_DEVICE_ID) {
    return false;
}

return _init(sensor_id);
```

# Replace it with
```cpp
Adafruit_BusIO_Register chip_id =
    Adafruit_BusIO_Register(i2c_dev, MPU6050_WHO_AM_I, 1);

// Read the WHO_AM_I register
uint8_t id = chip_id.read();

Serial.print("WHO_AM_I = 0x");
Serial.println(id, HEX);

// Accept both MPU6050 (0x68) and MPU6500/compatible (0x70)
if (id != 0x68 && id != 0x70) {
    return false;
}

return _init(sensor_id);
```