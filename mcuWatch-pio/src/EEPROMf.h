DateTime readEEPROMdatetime(int EEPROMaddress)
{
    DateTime dtAnswer;

    debugMessln("Initializing EEPROM ...");
    EEPROM.begin(EEPROM_SIZE); // initialize EEPROM

    debugMessln("Reading EEPROM ...");
    EEPROM.get(EEPROMaddress, dtAnswer);

    // debugMess("Value: ");
    // debugMessln(dtAnswer);

    debugMessln("Closing EEPROM ...");
    EEPROM.end();

    return dtAnswer;
}

byte readEEPROMbyte(int EEPROMaddress)
{
    byte byteAnswer;

    debugMessln("Initializing EEPROM ...");
    EEPROM.begin(EEPROM_SIZE); // initialize EEPROM

    debugMessln("Reading EEPROM ...");
    EEPROM.get(dtNtpAddress, byteAnswer);

    debugMess("Value: ");
    debugMessln(byteAnswer);

    debugMessln("Closing EEPROM ...");
    EEPROM.end();

    debugMessln();

    return byteAnswer;
}

boolean isDT(int EEPROMaddress)
{
    debugMessln("Checking if EEPROM holds a time stamp ...");

    byte value = readEEPROMbyte(EEPROMaddress);

    if (value == 0 || value == 255)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void getDtNTP()
{
    if (isDT(dtNtpAddress))
    {
        dtNTP = readEEPROMdatetime(dtNtpAddress + 1);

        debugMessln("Time when RTC was synced with an ntp server: ");

        prettyPrintDateTime(dtNTP);

        debugMessln();
    }
    else
    {
        debugMessln("No time stamp stored");
    }
}