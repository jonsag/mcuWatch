
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
            if (i != 0)
            {
                debug(", ");
            }
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

        myDS3231.setClockMode(false); // set to 24h
        // setClockMode(true); // set to 12h

        myDS3231.setYear(year);
        myDS3231.setMonth(month);
        myDS3231.setDate(date);
        myDS3231.setDoW(dOW);
        myDS3231.setHour(hour);
        myDS3231.setMinute(minute);
        myDS3231.setSecond(second);

        /*
        // Test of alarm functions
        // set A1 to one minute past the time we just set the clock
        // on current day of week.
        myDS3231.setA1Time(dOW, hour, minute + 1, second, 0x0, true,
                        false, false);
        // set A2 to two minutes past, on current day of month.
        myDS3231.setA2Time(date, hour, minute + 2, 0x0, false, false,
                        false);
        // Turn on both alarms, with external interrupt
        myDS3231.turnOnAlarm(1);
        myDS3231.turnOnAlarm(2);
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

DateTime timeNow()
{
    return myRTClib.now();
}

void getTime()
{
    // DateTime now = myRTClib.now();

    /*
    yearNow = (myDS3231.getYear(), DEC);
    monthNow = (myDS3231.getMonth(century), DEC);
    dateNow = (myDS3231.getDate(), DEC);
    hourNow = (myDS3231.getHour(h12Flag, pmFlag), DEC); // 24-hr
    minuteNow = (myDS3231.getMinute(), DEC);
    secondNow = (myDS3231.getSecond(), DEC);
*/

    now = timeNow();

#if DEBUG
    Serial.print("From RTC: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
#endif

    yearNow = (now.year(), DEC);
    monthNow = (now.month(), DEC);
    dateNow = (now.day(), DEC);
    hourNow = (now.hour(), DEC); // 24-hr
    minuteNow = (now.minute(), DEC);
    secondNow = (now.second(), DEC);
}

void printRawTime(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
#if DEBUG
    Serial.print(year);
    Serial.print("-");
    Serial.print(month);
    Serial.print("-");
    Serial.print(date);
    Serial.print(" ");
    Serial.print(hour); // 24-hr
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);
#endif
}

void printFormattedTime(byte &year, byte &month, byte &date, byte &dOW,
                        byte &hour, byte &minute, byte &second)
{
#if DEBUG
    Serial.print(padByte(year));
    Serial.print("-");
    Serial.print(padByte(month));
    Serial.print("-");
    Serial.print(padByte(date));
    Serial.print(" ");
    Serial.print(padByte(hour)); // 24-hr
    Serial.print(":");
    Serial.print(padByte(minute));
    Serial.print(":");
    Serial.println(padByte(second));
#endif
}

void printTime()
{
#if DEBUG
    Serial.print(padByte(yearNow));
    Serial.print("-");
    Serial.print(padByte(monthNow));
    Serial.print("-");
    Serial.print(padByte(dateNow));
    Serial.print(" ");
    Serial.print(padByte(hourNow)); // 24-hr
    Serial.print(":");
    Serial.print(padByte(minuteNow));
    Serial.print(":");
    Serial.println(padByte(secondNow));
#endif
}
void printUNIXtime()
{
    now = timeNow();

#if DEBUG
    Serial.println();
    Serial.print("Since midnight 1/1/1970: ");
    Serial.print(now.unixtime());
    Serial.print(" s, ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
#endif
}

void printTemp()
{
#if DEBUG
    Serial.println();
    Serial.print("Temp: ");
    Serial.println((myDS3231.getTemperature(), 2));
#endif
}

void RTCtest()
{
    // now = myRTClib.now();
    now = timeNow();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    Serial.println();
}