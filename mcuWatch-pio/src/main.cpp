#include <Arduino.h>

#include "config.h"

#include "set.h"
#include "screenTest.h"

void setup()
{
    // Start the serial port
    Serial.begin(57600);

    // Start the I2C interface
    Wire.begin();

    Serial.print(F("Hello! ST77xx TFT Test"));

    // Use this initializer if using a 1.8" TFT screen:
    tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab

    // OR use this initializer if using a 1.8" TFT screen with offset such as WaveShare:
    // tft.initR(INITR_GREENTAB);      // Init ST7735S chip, green tab

    // OR use this initializer (uncomment) if using a 1.44" TFT:
    // tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab

    // OR use this initializer (uncomment) if using a 0.96" 160x80 TFT:
    // tft.initR(INITR_MINI160x80);  // Init ST7735S mini display

    // OR use this initializer (uncomment) if using a 1.3" or 1.54" 240x240 TFT:
    // tft.init(240, 240);           // Init ST7789 240x240

    // OR use this initializer (uncomment) if using a 1.69" 280x240 TFT:
    // tft.init(240, 280);           // Init ST7789 280x240

    // OR use this initializer (uncomment) if using a 2.0" 320x240 TFT:
    // tft.init(240, 320);           // Init ST7789 320x240

    // OR use this initializer (uncomment) if using a 1.14" 240x135 TFT:
    // tft.init(135, 240);           // Init ST7789 240x135

    // OR use this initializer (uncomment) if using a 1.47" 172x320 TFT:
    // tft.init(172, 320);           // Init ST7789 172x320

    // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
    // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
    // may end up with a black screen some times, or all the time.
    // tft.setSPISpeed(40000000);

    Serial.println(F("Initialized"));

    uint16_t time = millis();
    tft.fillScreen(ST77XX_BLACK);
    time = millis() - time;

    Serial.println(time, DEC);
    delay(500);

    // large block of text
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
    delay(1000);
/*
    // tft print function!
    tftPrintTest();
    delay(4000);

    // a single pixel
    tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
    delay(500);

    // line draw test
    testlines(ST77XX_YELLOW);
    delay(500);

    // optimized lines
    testfastlines(ST77XX_RED, ST77XX_BLUE);
    delay(500);

    testdrawrects(ST77XX_GREEN);
    delay(500);

    testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
    delay(500);

    tft.fillScreen(ST77XX_BLACK);
    testfillcircles(10, ST77XX_BLUE);
    testdrawcircles(10, ST77XX_WHITE);
    delay(500);

    testroundrects();
    delay(500);

    testtriangles();
    delay(500);

    mediabuttons();
    delay(500);
*/
    Serial.println("done");
    delay(1000);
}

void loop()
{
    tft.invertDisplay(true);
    delay(500);
    tft.invertDisplay(false);
    delay(500);
}

