
void getDateStuff(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    // based on an examples at
    // https://arduinogetstarted.com/reference/serial-readbytes
    // https://arduinogetstarted.com/reference/serial-readbytesuntil
    // https://arduinogetstarted.com/reference/serial-settimeout

    const int BUFFER_SIZE = 12;
    char buf[BUFFER_SIZE], inString[BUFFER_SIZE];
    byte temp1, temp2;
    int rlen, rxlen;

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

    Serial.print("I got: ");
    Serial.print(inString);

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

        Serial.println("Preparing to set RTC...");

        getDateStuff(year, month, date, dOW, hour, minute, second);

        //          year, month, date, hour, min, sec and week-day
        DateTime dt(year, month, date, hour, minute, second, dOW);
        rtc.setDateTime(dt);

        /*
                myDS3231.setClockMode(false); // set to 24h
                // setClockMode(true); // set to 12h

                myDS3231.setYear(year);
                myDS3231.setMonth(month);
                myDS3231.setDate(date);
                myDS3231.setDoW(dOW);
                myDS3231.setHour(hour);
                myDS3231.setMinute(minute);
                myDS3231.setSecond(second);
        */

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
        Serial.print("Time is set!");
    }
}

void adjustDate(int year, int month, int date, int hour, int min, int sec, int weekday)
{
    DateTime dt(year, month, date, hour, min, sec, weekday);
    rtc.setDateTime(dt); // Adjust date-time as defined 'dt' above
    // Serial.println(rtc.now().getEpoch());//debug info
}

String padByte(String &s)
{
    String myString = s;
    if (myString.length() < 2)
    {
        myString = "0" + myString;
    }

    return myString;
}

DateTime timeNow()
{
    return rtc.now();
}

float tempNow()
{
    rtc.convertTemperature();
    return rtc.getTemperature();
}

void RTCtest(DateTime &now)
{
#if DEBUG
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.date(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
#endif
}

void printUNIXtime(DateTime &now)
{
#if DEBUG
    Serial.print("Since midnight 1/1/1970: ");
    Serial.print(now.getEpoch());
    Serial.print("s, ");
    Serial.print(now.getEpoch() / 86400L);
    Serial.println("d");
#endif
}

void printTemp()
{
#if DEBUG
    rtc.convertTemperature();
    Serial.print(rtc.getTemperature()); // read registers and display the temperature
    Serial.println("deg C");
#endif
}

String prettyNumbering(String &k)
{
    char last = k.charAt(k.length() - 1);
    int l = (int)(last - '0');

    switch (l)
    {
    case 1:
        return k + "st";
        break;
    case 2:
        return k + "nd";
        break;
    case 3:
        return k + "rd";
        break;
    default:
        return k + "th";
        break;
    }
}

void prettyPrint(DateTime &now, float temperature)
{
    String temp;

    //#if DEBUG
    temp = now.hour() - DST;
    Serial.print(padByte(temp));
    Serial.print(":");

    temp = now.minute();
    Serial.print(padByte(temp));
    Serial.print(":");

    temp = now.second();
    Serial.print(padByte(temp));
    Serial.print(" ");

    Serial.print(dayName[now.dayOfWeek()]);
    Serial.print(" ");

    Serial.print(monthName[now.month() - 1]);
    Serial.print(" ");

    temp = now.date();
    Serial.print(prettyNumbering(temp));
    Serial.print(" ");

    temp = now.year();
    Serial.println(padByte(temp));

    Serial.print("Temperature: ");
    Serial.println(temperature);

    debugln();
    //#endif
}
