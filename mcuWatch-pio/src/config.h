
/**********
 * TFT screen
 **********/
/*
SPI (ST7735)
Function    Screen pin  Arduino 168 Arduino 328 ESP8266     ESP-01      Comment
-----       -----       -----       -----       -----       -----       -----
SCK         3           D9          D13*)       D5/GPIO14*)             SCL, HSCLK, SPI Clock, Hardware SPI clk
SDA         4           D8          D11*)       D7/GPIO13*)             SPI Data, MOSI, HMOSI, data to screen
RES         pulled high                                                 RST, HMISO, screen reset
DC          6           D6          D7          D4/GPIO2                Register Select, labelled as DC in Adafruit code
CS          7           D5          D6          D3/GPIO0                Chip Select, defined as Slave Select in SPI
*) Must be these pins as they are set in firmware/hardware
*/

#include <SPI.h>

int const cs = 6; // TFT display SPI chip select pin
int const dc = 7; // TFT display data/command select pin

// Display parameters - uncomment the line for the one you want to userotate = 0;

// Adafruit 1.8" 160x128 display
 int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 0;

// AliExpress 1.8" 160x128 display
//int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 0;

#include <TFTGraphicsLibrary.h> // this line must come after definitions of cs/dc pins
