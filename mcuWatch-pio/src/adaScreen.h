
void clearScreen()
{
  tft.fillScreen(bgCol);
}

void helpLines()
{
#if DEBUG
  for (int i = tft.height() / 4; i < tft.height(); i += tft.height() / 4)
  {
    Serial.print("0, ");
    Serial.print(i);
    Serial.print(" -> ");
    Serial.print(tft.width() - 1);
    Serial.print(", ");
    Serial.println(i);

    tft.drawLine(0, i, tft.width() - 1, i, colGre);
  }

  for (int i = tft.width() / 4; i < tft.width(); i += tft.width() / 4)
  {
    Serial.print(i);
    Serial.print(", 0 -> ");
    Serial.print(i);
    Serial.print(", ");
    Serial.println(tft.height() - 1);

    tft.drawLine(i, 0, i, tft.height() - 1, colGre);
  }
#endif
}

void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
  debug("Filling rectangle, x: ");
  debug(x);
  debug("\t y: ");
  debug(y);
  debug("\t width: ");
  debug(width);
  debug("\t height: ");
  debug(height);
  debug("\t colour: ");
  debugln(color);
  tft.fillRect(x, y, width, height, color);
}

void drawText(int16_t posX, int16_t posY, int16_t size, uint16_t color, String inText)
{
  debug("Drawing text, x: ");
  debug(posX);
  debug("\t y: ");
  debug(posY);
  debug("\t size: ");
  debug(size);
  debug("\t colour: ");
  debug(color);
  debug("\ttext: ");
  debugln(inText);

  tft.setCursor(posX, posY);
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(inText);
}

void printTime(DateTime &now)
{
  String temp1, temp2;

  info("+++++ Writing new time: ");

  temp1 = now.hour() + hourOffs;
  temp2 = padByte(temp1);
  temp2 += ":";
  temp1 = now.minute();
  temp2 += padByte(temp1);

  infoln(temp2);

  fillRectangle(tft.width() / 2 - temp2.length() / 2.0 * pixX * timeSize + timeXOffs, // x
                tft.height() / 8 * timeNowYPos,                                       // y
                temp2.length() * pixX * timeSize,                                     // width
                pixY * timeSize,                                                      // height
                bgCol);                                                               // colour

  drawText(tft.width() / 2 - temp2.length() / 2.0 * pixX * timeSize + timeXOffs, // x
           tft.height() / 8 * timeNowYPos,                                       // y
           timeSize,                                                             // size
           timeCol,                                                              // colour
           temp2);                                                               // text
}

void printDate(DateTime &now)
{
  String temp1, temp2;

  info("+++++ Writing new date: ");

  temp2 = dayName[now.dayOfWeek() - 1];
  temp2 += " ";
  temp2 += monthName[now.month() - 1];
  temp2 += " ";
  temp1 = now.date();
  temp2 += prettyNumbering(temp1);
  temp2 += " ";
  temp1 = now.year();
  temp2 += padByte(temp1);

  infoln((temp2));

  fillRectangle(tft.width() / 2 - (temp2.length() + 1) / 2.0 * pixX * dateSize, // x
                tft.height() / 8 * dateYPos,                                    // y
                (temp2.length() + 1) * pixX * dateSize,                         // width
                pixY * dateSize,                                                // height
                bgCol);                                                         // colour

  drawText(tft.width() / 2 - temp2.length() / 2.0 * pixX * dateSize, // x
           tft.height() / 8 * dateYPos,                              // y
           dateSize,                                                 // size
           dateCol,                                                  // colour
           temp2);                                                   // text
}

void printTemp(float temperature)
{
  char temp1[4];
  String temp2;

  info("+++++ Writing new temp: ");

  // temp2 = String(temperature, 1);
  dtostrf(temperature, 4, 1, temp1);
  temp2 = String(temp1);

  infoln(temp2);

  fillRectangle(tft.width() / 2 - (temp2.length() + 1) / 2.0 * pixX * tempNowSize, // x
                tft.height() / 8 * tempNowYPos,                                    // y
                (temp2.length() + 1) * pixX * tempNowSize,                         // width
                pixY * tempNowSize,                                                // height
                bgCol);                                                            // colour

  drawText(tft.width() / 2 - temp2.length() / 2.0 * pixX * tempNowSize, // x
           tft.height() / 8 * tempNowYPos,                              // y
           tempNowSize,                                                 // size
           tempCol,                                                     // colour
           temp2);                                                      // text

  if (temperature > maxTemp)
  {
    infoln("+++++ New max temp");

    fillRectangle(tft.width() / 4 * 3 - (temp2.length() + 1) / 2.0 * pixX * tempSize, // x
                  tft.height() / 8 * tempMinMaxYPos,                                  // y
                  (temp2.length() + 1) * pixX * tempSize,                             // width
                  pixY * tempSize,                                                    // height
                  bgCol);                                                             // colour

    drawText(tft.width() / 4 * 3 - temp2.length() / 2.0 * pixX * tempSize, // x
             tft.height() / 8 * tempMinMaxYPos,                            // y
             tempSize,                                                     // size
             maxTempCol,                                                   // colour
             temp2);                                                       // text

    maxTemp = temperature;
    // maxTempNow = now;
  }

  if (temperature < minTemp)
  {
    infoln("+++++ New min temp");

    fillRectangle(tft.width() / 4 - (temp2.length() + 1) / 2.0 * pixX * tempSize, // x
                  tft.height() / 8 * tempMinMaxYPos,                              // y
                  (temp2.length() + 1) * pixX * tempSize,                         // width
                  pixY * tempSize,                                                // height
                  bgCol);                                                         // colour

    drawText(tft.width() / 4 - temp2.length() / 2.0 * pixX * tempSize, // x
             tft.height() / 8 * tempMinMaxYPos,                        // y
             tempSize,                                                 // size
             minTempCol,                                               // colour
             temp2);                                                   // text

    minTemp = temperature;
    // minTempNow = now;
  }
}

void updateScreen(DateTime &now, float temperature)
{
  String temp1, temp2;

  temp1 = now.date();
  temp2 = oldNow.date();
  if (temp1 != temp2)
  {
    debugln("----- Updating screen, date ...");
    printDate(now);
  }

  temp1 = now.minute();
  temp2 = oldNow.minute();
  if (temp1 != temp2)
  {
    debugln("----- Updating screen, time ...");
    printTime(now);

    oldNow = now;
  }

  if (temperature != oldTemp)
  {
    debugln("----- Updating screen, temperature ...");

    printTemp(temperature);

    oldTemp = temperature;
  }

  debugln();
}