
/**********
 * TFT screen
 **********/
/*
SPI (ST7735)
Function    Screen pin  Arduino 168 Arduino 328 ESP8266     ESP-01      Comment
-----       -----       -----       -----       -----       -----       -----
SCK         3           D13*)        D13*)       D5/GPIO14*)             SCL, HSCLK, SPI Clock, Hardware SPI clk
SDA         4           D11*)        D11*)       D7/GPIO13*)             SPI Data, MOSI, HMOSI, data to screen
RES         pulled high                                                 RST, HMISO, screen reset
DC          6           D5          D5          D4/GPIO2                Register Select, labelled as DC in Adafruit code
CS          7           D4          D4          D3/GPIO0                Chip Select, defined as Slave Select in SPI
*) Must be these pins as they are set in firmware/hardware
*/

#include <SPI.h>

#if defined(ESP8266)
#define dc 2   // D4/GPIO2
#define cs 0   // D3/GPIO0

#else
#define dc 5 // TFT display SPI chip select pin
#define cs 4 // TFT display data/command select pin

#endif

// define screen
/*
rotate:
0: no rotation
3: 90 degrees CW
6: 180 degrees
5: 90 degrees CCW
*/
int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 0; // Adafruit 1.8" 160x128 display

#include <TFTGraphicsLibrary.h> // this line must come after definitions of cs/dc pins

/**********
 * RTC
 **********/
/*I2C (RTC and SSD1306)
Function    RTC         Screen      Arduino     ESP8266     ESP-01
-----       -----       -----       -----       -----       -----
Address     0x68        0x3C
SDA         2                       A4          D2/GPIO4    3/GPIO2
SCL         3                       A5          D1/GPIO5    5/GPIO0
*/

#include <DS3231.h>
//#include <Wire.h> // included by the SPI-include above

DS3231 myRTC;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

bool century = false;
bool h12Flag;
bool pmFlag;

long currentMillis;
long lastTickMillis;
int tickInterval = 1000;

/**********
 * Rotary encoder
 **********/
/*
Rotary encoder
Function    Arduino 168 Arduino 328 ESP8266     ESP-01
-----       -----       -----       -----       -----
CLK                     D9
DT                      D8
SW                      D7
*/

/**********
 * Buzzer
 **********/
/*
Buzzer
Function    Arduino 168 Arduino 328 ESP8266     ESP-01
-----       -----       -----       -----       -----
+                       D6
*/

/**********
 * Misc
 **********/

int i = 0;