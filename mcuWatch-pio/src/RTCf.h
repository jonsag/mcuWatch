
void getDateStuff(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    // boolean gotString = false;
    /*
    char inChar;
    byte temp1, temp2;
    char inString[20];
    byte j = 0;

    // while (!gotString)
    while (true)
    {
        if (Serial.available())
        {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x')
            {
                // gotString = true;
                break;
            }
        }
    }
*/

    // based on an examples at
    // https://arduinogetstarted.com/reference/serial-readbytes
    // https://arduinogetstarted.com/reference/serial-readbytesuntil
    // https://arduinogetstarted.com/reference/serial-settimeout
    char inString[20];
    byte temp1, temp2;

    rxlen = Serial.available(); // number of bytes available in Serial buffer
    if (rxlen > 0)              // read only the fixed number of bytes in buffer
    {
        if (rxlen > BUFFER_SIZE)
        {                       // check if the data exceeds the buffer size
            rlen = BUFFER_SIZE; // if yes, read BUFFER_SIZE bytes. The remaining will be read in the next time
        }
        else
        {
            rlen = rxlen;
        }

        // read the incoming bytes:
        rlen = Serial.readBytesUntil('x', buf, BUFFER_SIZE);

        // prints the received data
        debug("I received: ");
        for (int i = 0; i < rlen; i++)
        {
            debug(buf[i]);
            inString[i] = buf[i];
        }
        debugln();

        debug("Number of chars: ");
        debugln(rlen);

        while (Serial.available()) // clear buffer
        {
            Serial.read();
        }
    }

    debug("I got: ");
    debugln(inString);

    temp1 = (byte)inString[0] - 48; // Read year first
    temp2 = (byte)inString[1] - 48;
    year = temp1 * 10 + temp2;
    debug("Year: ");
    debugln(year);

    temp1 = (byte)inString[2] - 48; // now month
    temp2 = (byte)inString[3] - 48;
    month = temp1 * 10 + temp2;
    debug("Month: ");
    debugln(month);

    temp1 = (byte)inString[4] - 48; // now date
    temp2 = (byte)inString[5] - 48;
    date = temp1 * 10 + temp2;
    debug("Date: ");
    debugln(date);

    dOW = (byte)inString[6] - 48; // now Day of Week
    debug("Dow: ");
    debugln(dOW);

    temp1 = (byte)inString[7] - 48; // now hour
    temp2 = (byte)inString[8] - 48;
    hour = temp1 * 10 + temp2;
    debug("Hour: ");
    debugln(hour);

    temp1 = (byte)inString[9] - 48; // now minute
    temp2 = (byte)inString[10] - 48;
    minute = temp1 * 10 + temp2;
    debug("Minute: ");
    debugln(minute);

    temp1 = (byte)inString[11] - 48; // now second
    temp2 = (byte)inString[12] - 48;
    second = temp1 * 10 + temp2;
    debug("Second: ");
    debugln(second);
}

void setTime()
{

    // If something is coming in on the serial line, it's
    // a time correction so set the clock accordingly.
    if (Serial.available())
    {
        // clockIsSet = false;

        debugln("Preparing to set RTC...");

        getDateStuff(year, month, date, dOW, hour, minute, second);

        myRTC.setClockMode(false); // set to 24h
        // setClockMode(true); // set to 12h

        myRTC.setYear(year);
        myRTC.setMonth(month);
        myRTC.setDate(date);
        myRTC.setDoW(dOW);
        myRTC.setHour(hour);
        myRTC.setMinute(minute);
        myRTC.setSecond(second);

        /*
        // Test of alarm functions
        // set A1 to one minute past the time we just set the clock
        // on current day of week.
        myRTC.setA1Time(dOW, hour, minute + 1, second, 0x0, true,
                        false, false);
        // set A2 to two minutes past, on current day of month.
        myRTC.setA2Time(date, hour, minute + 2, 0x0, false, false,
                        false);
        // Turn on both alarms, with external interrupt
        myRTC.turnOnAlarm(1);
        myRTC.turnOnAlarm(2);
        */

        debugln();
        debugln("Finished!");
        // clockIsSet = true;
    }

    /*
        if (clockIsSet)
        {
            debugln("RTC is set");
            clockIsSet = false;
            debugln("Clearing serial buffer...");
            while (Serial.available())
                Serial.read();
        }
        */
}

String padByte(byte &k)
{
    String myString = String(k);
    if (myString.length() < 2)
    {
        myString = "0" + myString;
    }

    return myString;
}

void getTime()
{
    DateTime now = myRTC.now();

    /*
    yearNow = (myRTC.getYear(), DEC);
    monthNow = (myRTC.getMonth(century), DEC);
    dateNow = (myRTC.getDate(), DEC);
    hourNow = (myRTC.getHour(h12Flag, pmFlag), DEC); // 24-hr
    minuteNow = (myRTC.getMinute(), DEC);
    secondNow = (myRTC.getSecond(), DEC);
*/

    yearNow = (now.year(), DEC);
    monthNow = (now.month(), DEC);
    dateNow = (now.day(), DEC);
    hourNow = (now.hour(), DEC); // 24-hr
    minuteNow = (now.minute(), DEC);
    secondNow = (now.second(), DEC);

    debug("From RTC: ");
    debug(yearNow);
    debug("-");
    debug(monthNow);
    debug("-");
    debug(dateNow);
    debug(" ");
    debug(hourNow); // 24-hr
    debug(":");
    debug(minuteNow);
    debug(":");
    debugln(secondNow);
}

void printRawTime(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    debug(year);
    debug("-");
    debug(month);
    debug("-");
    debug(date);
    debug(" ");
    debug(hour); // 24-hr
    debug(":");
    debug(minute);
    debug(":");
    debugln(second);
}

void printFormattedTime(byte &year, byte &month, byte &date, byte &dOW,
                        byte &hour, byte &minute, byte &second)
{
    debug(padByte(year));
    debug("-");
    debug(padByte(month));
    debug("-");
    debug(padByte(date));
    debug(" ");
    debug(padByte(hour)); // 24-hr
    debug(":");
    debug(padByte(minute));
    debug(":");
    debugln(padByte(second));
}