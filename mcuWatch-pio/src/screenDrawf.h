
void clearScreen()
{
#if OLEDSCREEN
  myScreen.clearDisplay();

#elif TFTSCREEN
  myScreen.fillScreen(bgCol);

#endif
}

void helpLines()
{
#if DEBUG
  debugMessln("Drawing horizontal lines ...");
  for (int i = myScreen.height() / YSplits; i < myScreen.height(); i += myScreen.height() / YSplits) // horizontal lines
  {
    Serial.print("0, ");
    Serial.print(i);
    Serial.print(" -> ");
    Serial.print(myScreen.width() - 1);
    Serial.print(", ");
    Serial.println(i);

    myScreen.drawLine(0, i, myScreen.width() - 1, i, helpLineCol);
  }

  debugMessln("Drawing vertical lines ...");
  for (int i = myScreen.width() / XSplits; i < myScreen.width(); i += myScreen.width() / XSplits) // vertical lines
  {
    Serial.print(i);
    Serial.print(", 0 -> ");
    Serial.print(i);
    Serial.print(", ");
    Serial.println(myScreen.height() - 1);

    myScreen.drawLine(i, 0, i, myScreen.height() - 1, helpLineCol);
  }

#if OLEDSCREEN
  myScreen.display(); // update screen with drawn lines

#endif

#endif
}

void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
  debugMess("Filling rectangle, x: ");
  debugMess(x);
  debugMess("\ty: ");
  debugMess(y);
  debugMess("\twidth: ");
  debugMess(width);
  debugMess("\theight: ");
  debugMess(height);
  debugMess("\tcolour: ");
  debugMessln(color);
  myScreen.fillRect(x, y, width, height, color);

#if OLEDSCREEN
  myScreen.display(); // update screen

#endif
}

void drawText(int16_t posX, int16_t posY, int16_t size, uint16_t color, String inText)
{
  debugMess("Drawing text, x: ");
  debugMess(posX);
  debugMess("\ty: ");
  debugMess(posY);
  debugMess("\tsize: ");
  debugMess(size);
  debugMess("\tcolour: ");
  debugMess(color);
  debugMess("\ttext: ");
  debugMessln(inText);

  myScreen.setCursor(posX, posY);
  myScreen.setTextSize(size);
  myScreen.setTextColor(color);
  myScreen.setTextWrap(true);
  myScreen.print(inText);

#if OLEDSCREEN
  myScreen.display(); // update screen

#endif
}

void printStartMess(String inText, int YPos)
{
  drawText(myScreen.width() / 2 - inText.length() / 2.0 * pixX * startSize, // x
           myScreen.height() / YSplits * YPos,                              // y
           dateSize,                                                        // size
           startCol,                                                        // colour
           inText);
}
void printIP()
{
  String myString;

#if WEBSERVER
  infoMess("+++++ Writing SSID and IP ...");

  myString = "Connected to:";
  printStartMess(myString, 0);

  myString = ssid;
  printStartMess(myString, 1);

  myString = "IP:";
  printStartMess(myString, 2);

  myString = WiFi.localIP().toString();
  printStartMess(myString, 3);

#else
  myString = "No web server";
  printStartMess(myString, 0);

#endif

#if OLEDSCREEN
  myScreen.display(); // update screen

#endif
}

void printDate(DateTime &now)
{
  String myString;

  infoMess("+++++ Writing new date: ");

  myString = dayName[now.dayOfWeek() - 1];
  myString.concat(" ");
  myString.concat(monthName[now.month() - 1]);
  myString.concat(" ");
  myString.concat(now.date());
  myString.concat(prettyNumbering(now.date()));
  myString.concat(" ");
  myString.concat(now.year());

  infoMessln((myString));

  fillRectangle(myScreen.width() / XSplits * dateXPos - (myString.length() + 1) / 2.0 * pixX * dateSize, // x
                myScreen.height() / YSplits * dateYPos,                                                  // y
                (myString.length() + 1) * pixX * dateSize,                                               // width
                pixY * dateSize,                                                                         // height
                bgCol);                                                                                  // colour

  drawText(myScreen.width() / XSplits * dateXPos - myString.length() / 2.0 * pixX * dateSize, // x
           myScreen.height() / YSplits * dateYPos,                                            // y
           dateSize,                                                                          // size
           dateCol,                                                                           // colour
           myString);                                                                         // text

#if OLEDSCREEN
  myScreen.display(); // update screen

#endif
}

void printTime(DateTime &now)
{
  String myString;

  infoMess("+++++ Writing new time: ");

  myString = padByte((now.hour() + hourOffs)) + ":";
  myString.concat(padByte(now.minute()));

  infoMessln(myString);

  fillRectangle(myScreen.width() / XSplits * timeNowXPos - myString.length() / 2.0 * pixX * timeSize + timeXOffs, // x
                myScreen.height() / YSplits * timeNowYPos,                                                        // y
                myString.length() * pixX * timeSize,                                                              // width
                pixY * timeSize,                                                                                  // height
                bgCol);                                                                                           // colour

  drawText(myScreen.width() / XSplits * timeNowXPos - myString.length() / 2.0 * pixX * timeSize + timeXOffs, // x
           myScreen.height() / YSplits * timeNowYPos,                                                        // y
           timeSize,                                                                                         // size
           timeCol,                                                                                          // colour
           myString);                                                                                        // text

#if OLEDSCREEN
  myScreen.display(); // update screen

#endif
}

void printTemp(float temperature)
{
  char myString1[4];
  String myString2;

  infoMess("+++++ Writing new temperature: ");

  dtostrf(temperature, 4, 1, myString1);
  myString2 = String(myString1);

  infoMessln(myString2);

  fillRectangle(myScreen.width() / XSplits * tempNowXPos - (myString2.length() + 1) / 2.0 * pixX * tempNowSize, // x
                myScreen.height() / YSplits * tempNowYPos,                                                      // y
                (myString2.length() + 1) * pixX * tempNowSize,                                                  // width
                pixY * tempNowSize,                                                                             // height
                bgCol);                                                                                         // colour

  drawText(myScreen.width() / XSplits * tempNowXPos - myString2.length() / 2.0 * pixX * tempNowSize, // x
           myScreen.height() / YSplits * tempNowYPos,                                                // y
           tempNowSize,                                                                              // size
           tempCol,                                                                                  // colour
           myString2);                                                                               // text

  if (temperature > maxTemp)
  {
    infoMessln("+++++ New max temperature");

    fillRectangle(myScreen.width() / XSplits * tempMaxXpos - (myString2.length() + 1) / 2.0 * pixX * tempSize, // x
                  myScreen.height() / YSplits * tempMaxYPos,                                                   // y
                  (myString2.length() + 1) * pixX * tempSize,                                                  // width
                  pixY * tempSize,                                                                             // height
                  bgCol);                                                                                      // colour

    drawText(myScreen.width() / XSplits * tempMaxXpos - myString2.length() / 2.0 * pixX * tempSize, // x
             myScreen.height() / YSplits * tempMaxYPos,                                             // y
             tempSize,                                                                              // size
             maxTempCol,                                                                            // colour
             myString2);                                                                            // text

    maxTemp = temperature;
    // maxTempNow = now;
  }

  if (temperature < minTemp)
  {
    infoMessln("+++++ New min temperature");

    fillRectangle(myScreen.width() / XSplits * tempMinXpos - (myString2.length() + 1) / 2.0 * pixX * tempSize, // x
                  myScreen.height() / YSplits * tempMinYPos,                                                   // y
                  (myString2.length() + 1) * pixX * tempSize,                                                  // width
                  pixY * tempSize,                                                                             // height
                  bgCol);                                                                                      // colour

    drawText(myScreen.width() / XSplits * tempMinXpos - myString2.length() / 2.0 * pixX * tempSize, // x
             myScreen.height() / YSplits * tempMinYPos,                                             // y
             tempSize,                                                                              // size
             minTempCol,                                                                            // colour
             myString2);                                                                            // text

    minTemp = temperature;
    // minTempNow = now;
  }

#if OLEDSCREEN
  myScreen.display(); // update screen

#endif
}

void updateScreen(DateTime &now, float temperature)
{
  if (now.date() != oldNow.date())
  {
    debugMessln("----- Updating screen, date ...");
    printDate(now);
  }

  if (now.minute() != oldNow.minute())
  {
    debugMessln("----- Updating screen, time ...");
    printTime(now);
    oldNow = now;
  }

  if (temperature != oldTemp)
  {
    debugMessln("----- Updating screen, temperature ...");
    printTemp(temperature);

    oldTemp = temperature;
  }

  debugMessln();
}
