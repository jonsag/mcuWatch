# Serial Communication HowTo

## Find the device

>$ dmesg

    ...
    [256966.875728] usb 1-1.4: ch341-uart converter now attached to ttyUSB0

## CLI software

### picocom

[picocom @ github](https://github.com/npat-efault/picocom)  
[picocom man page](https://linux.die.net/man/8/picocom)  

Connect  
>$ picocom -b 115200 /dev/ttyUSB0 --omap crcrlf  

    picocom v3.1
    ...
    Type [C-a] [C-h] to see available commands
    Terminal ready

Turn on local echo  
> [Ctrl+a] [Ctrl+c]

    *** local echo: yes ***

Exit  

> [Ctrl+a] [Ctrl+x]

    Terminating...
    Thanks for using picocom

### cu

[cu @ github](https://github.com/nedko/cu)  
[cu man page](https://linux.die.net/man/1/cu)  

A simple serial monitor  

>$ cu -l /dev/ttyACM0 -s 9600

Exit
> ~. (tilde dot)  

### screen

[screen man page](https://linux.die.net/man/1/screen)  

Connect  

>$ screen /dev/ttyUSB0 9600


### mincom

[minicom @ github](https://github.com/Distrotech/minicom)  
[minicom man page](https://linux.die.net/man/1/minicom)  


### GUI software

[CuteCom](http://cutecom.sourceforge.net/)  

## ESP-01

### If you have AT firmware, for example an ESP-01

Check for AT firmware  
>AT

    OK

Check version  

>AT+GMR

    AT version:1.7.4.0(May 11 2020 19:13:04)
    SDK version:3.0.4(9532ceb)
    compile time:May 27 2020 10:12:17
    Bin version(Wroom 02):1.7.4
    OK
