#include <Arduino.h>

#include "config.h"
#include "drawScreen.h"
#include "RTCf.h"

// Setup **********************************************>

void setup()
{
  // Start the serial port
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  Serial.println("Compact TFT Graphics library");
  Serial.println();

  Serial.println("Initializing display ...");
  InitDisplay();
  Serial.println("Clearing display ...");
  ClearDisplay();
  Serial.println("Turning on display ...");
  DisplayOn();
  MoveTo(0, 0);

  Serial.println("Drawing frame...");
  TestFrame();
  Serial.println("Drawing large char...");
  TestChar();
  Serial.println("Drawing circle...");
  TestCircle();
  //Serial.println("Drawing text...");
  //TestText();

  Serial.println("Set time with YYMMDDwHHMMSS, with an 'x' at the end!");
  Serial.println("Delay...");
  delay(2000);
}

void loop()
{
  currentMillis = millis();

  setTime();

  if (currentMillis - lastTickMillis >= tickInterval)
  {
    i++;

    //Serial.println();
    Serial.print(i);
    Serial.print(":\t");
    Serial.print("Getting time...\t");

    // printTime();
    Serial.print(myRTC.getYear(), DEC);
    Serial.print("-");
    Serial.print(myRTC.getMonth(century), DEC);
    Serial.print("-");
    Serial.print(myRTC.getDate(), DEC);
    Serial.print(" ");
    Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC); // 24-hr
    Serial.print(":");
    Serial.print(myRTC.getMinute(), DEC);
    Serial.print(":");
    Serial.println(myRTC.getSecond(), DEC);
    
    lastTickMillis = currentMillis;
  }
}
