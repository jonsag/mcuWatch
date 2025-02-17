
void getDateStuff(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    // based on an examples at
    // https://arduinogetstarted.com/reference/serial-readbytes
    // https://arduinogetstarted.com/reference/serial-readbytesuntil
    // https://arduinogetstarted.com/reference/serial-settimeout

    const int BUFFER_SIZE = 15;
    char buf[BUFFER_SIZE], inString[BUFFER_SIZE];
    byte myString1, myString2;
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

        rlen = Serial.readBytesUntil('x', buf, BUFFER_SIZE); // read the incoming bytes

        debugMess("I received: "); // prints the received data
        for (int i = 0; i < rlen; i++)
        {
            if (i != 0)
            {
                debugMess(", ");
            }
            debugMess(buf[i]);
            inString[i] = buf[i];
        }
        debugMessln();

        debugMess("Number of chars: ");
        debugMessln(rlen);

        while (Serial.available()) // clear buffer
        {
            Serial.read();
        }
    }

    infoMess("I got: ");
    infoMess(inString);

    myString1 = (byte)inString[0] - 48; // Read year first
    myString2 = (byte)inString[1] - 48;
    year = myString1 * 10 + myString2;
    debugMess("Year: ");
    debugMessln(year);

    myString1 = (byte)inString[2] - 48; // now month
    myString2 = (byte)inString[3] - 48;
    month = myString1 * 10 + myString2;
    debugMess("Month: ");
    debugMessln(month);

    myString1 = (byte)inString[4] - 48; // now date
    myString2 = (byte)inString[5] - 48;
    date = myString1 * 10 + myString2;
    debugMess("Date: ");
    debugMessln(date);

    dOW = (byte)inString[6] - 48; // now Day of Week
    debugMess("Dow: ");
    debugMessln(dOW);

    myString1 = (byte)inString[7] - 48; // now hour
    myString2 = (byte)inString[8] - 48;
    hour = myString1 * 10 + myString2;
    debugMess("Hour: ");
    debugMessln(hour);

    myString1 = (byte)inString[9] - 48; // now minute
    myString2 = (byte)inString[10] - 48;
    minute = myString1 * 10 + myString2;
    debugMess("Minute: ");
    debugMessln(minute);

    myString1 = (byte)inString[11] - 48; // now second
    myString2 = (byte)inString[12] - 48;
    second = myString1 * 10 + myString2;
    debugMess("Second: ");
    debugMessln(second);
}

void setTime()
{
    // If something is coming in on the serial line, it's
    // a time correction so set the clock accordingly.
    if (Serial.available())
    {
        infoMessln("Preparing to set RTC...");

        getDateStuff(year, month, date, dOW, hour, minute, second);

        //          year, month, date, hour, min, sec and week-day
        DateTime dt(year, month, date, hour, minute, second, dOW);
        rtc.setDateTime(dt);

        debugMessln();
        infoMess("Time is set!");
    }
}

void adjustDate(int year, int month, int date, int hour, int min, int sec, int weekday)
{
    DateTime dt(year, month, date, hour, min, sec, weekday);
    rtc.setDateTime(dt); // adjust date-time as defined 'dt' above
}

DateTime RTCTimeNow()
{
    return rtc.now();
}

float RTCTempNow()
{
    rtc.convertTemperature();
    return rtc.getTemperature();
}

void RTCtest(DateTime now)
{
#if DEBUG
    Serial.print("----- RTC test: ");
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

String padByte(byte b)
{
    String myString = "";

    if (b < 10)
    {
        myString.concat("0");
    }

    myString.concat(b);

    return myString;
}

String prettyNumbering(byte b)
{
    if (b > 3 && b < 21)
    {
        return "th";
    }
    else
    {
        while (b > 9)
        {
            b = b - 10;
        }

        switch (b)
        {
        case 1:
            return "st";
            break;
        case 2:
            return "nd";
            break;
        case 3:
            return "rd";
            break;
        default:
            return "th";
            break;
        }
    }
}

void prettyPrintDateTime(DateTime &dt)
{
    Serial.print(padByte((dt.hour() + hourOffs)));
    Serial.print(":");

    Serial.print(padByte(dt.minute()));
    Serial.print(":");

    Serial.print(padByte(dt.second()));
    Serial.print(" ");

    Serial.print(dayName[dt.dayOfWeek() - 1]);
    Serial.print(" ");

    Serial.print(monthName[dt.month() - 1]);
    Serial.print(" ");

    Serial.print(dt.date());
    Serial.print(prettyNumbering(dt.date()));
    Serial.print(" ");

    Serial.println(dt.year());
}

void prettyPrint(DateTime &now, float temperature)
{
#if INFO || DEBUG
    /*
        Serial.print(padByte((now.hour() + hourOffs)));
        Serial.print(":");

        Serial.print(padByte(now.minute()));
        Serial.print(":");

        Serial.print(padByte(now.second()));
        Serial.print(" ");

        Serial.print(dayName[now.dayOfWeek() - 1]);
        Serial.print(" ");

        Serial.print(monthName[now.month() - 1]);
        Serial.print(" ");

        Serial.print(now.date());
        Serial.print(prettyNumbering(now.date()));
        Serial.print(" ");

        Serial.print(now.year());
    */
    prettyPrintDateTime(now);

    Serial.print("\t");
    debugMess("Temperature: ");
    Serial.println(temperature);

    debugMessln();

#endif
}
