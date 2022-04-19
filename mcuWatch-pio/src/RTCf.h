
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

        // read the incoming bytes:
        rlen = Serial.readBytesUntil('x', buf, BUFFER_SIZE);

        // prints the received data
        debugMess("I received: ");
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
        // clockIsSet = false;

        infoMessln("Preparing to set RTC...");

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

        debugMessln();
        infoMess("Time is set!");
    }
}

void adjustDate(int year, int month, int date, int hour, int min, int sec, int weekday)
{
    DateTime dt(year, month, date, hour, min, sec, weekday);
    rtc.setDateTime(dt); // Adjust date-time as defined 'dt' above
    // Serial.println(rtc.now().getEpoch());//debugMess info
}

String padByte(String &s)
{
    String myOtherString = s;
    if (myOtherString.length() < 2)
    {
        myOtherString = "0" + myOtherString;
    }

    return myOtherString;
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
#if INFO
    byte myByte; 
    String myString;

    myByte = now.hour() - hourOffs;
    if (myByte < 10) {
        Serial.print("0");
    }
    Serial.print(myByte);
    Serial.print(":");
/*
    myString = now.minute();
    Serial.print(padByte(myString));
    Serial.print(":");

    myString = now.second();
    Serial.print(padByte(myString));
    Serial.print(" ");

    Serial.print(dayName[now.dayOfWeek() - 1]);
    Serial.print(" ");

    Serial.print(monthName[now.month() - 1]);
    Serial.print(" ");

    myString = now.date();
    Serial.print(prettyNumbering(myString));
    Serial.print(" ");

    myString = now.year();
    Serial.println(padByte(myString));

    debugMess("Temperature: ");
    Serial.println(temperature);
*/
    debugMessln();
#endif
}
