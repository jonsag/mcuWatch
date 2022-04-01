#include <Arduino.h>

#include "config.h"

//#include "set.h"
#include "screenTests.h"

void setup()
{
    // Start the serial port
    Serial.begin(9600);

    // Start the I2C interface
    //Wire.begin();

    Serial.print(F("Hello! ST77xx TFT Test"));

    tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab

    // OR use this initializer if using a 1.8" TFT screen with offset such as WaveShare:
     tft.initR(INITR_GREENTAB);      // Init ST7735S chip, green tab

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

    // tft print function!
    tftPrintTest();
    delay(4000);
/*
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

