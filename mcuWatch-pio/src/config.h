/*

I2C
Function    RTC         Screen      Arduino     ESP8266     ESP-01
-----       -----       -----       -----       -----       -----
Address     0x68        0x3C
SDA         2           5           A4          D2/GPIO4    3/GPIO2
SCL         3           6           A5          D1/GPIO5    5/GPIO0

ST7735
Function    Arduino 168 Arduino 328 ESP8266     ESP-01
-----       -----       -----       -----       -----
CS          D5          
DC          D6
RES         D7
SDA         D8          D11
SCK         D9          D13

*/


/**********
 * RTC
 **********/
#include <DS3231.h>
#include <Wire.h>

DS3231 myRTC;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

/**********
 * Screen
 **********/
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
//#include <Adafruit_SSD1306.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS    5
  #define TFT_DC    6
  #define TFT_RST   7 // Or set to -1 and connect to Arduino RESET pin
#endif

// Hardware SPI pins
// For 1.44" and 1.8" TFT with ST7735 use:
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define TFT_MOSI 8
#define TFT_SCLK 9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

/**********
 * Misc
 **********/
float p = 3.1415926;