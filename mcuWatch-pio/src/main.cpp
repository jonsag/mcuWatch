#include <Arduino.h>

#include "config.h"

#include "set.h"

void setup() {
    // Start the serial port
    Serial.begin(57600);
    
    // Start the I2C interface
    Wire.begin();
}

void loop() {
    ds3231Set();
}