/*

Function    RTC         Screen      Arduino     ESP8266     ESP-01
-----       -----       -----       -----       -----       -----
Address     0x68        0x3C
SDA         2           5           A4          D2/GPIO4    3/GPIO2
SCL         3           6           A5          D1/GPIO5    5/GPIO0

*/

/**********
 * Load modules
 **********/
#include <DS3231.h>
#include <Wire.h>

#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**********
 * RTC
 **********/
DS3231 myRTC;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;
