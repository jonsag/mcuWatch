# ESP-01 HowTo

## Communication using picocom

Find device  
>$ dmesg

    ...
    [256966.875728] usb 1-1.4: ch341-uart converter now attached to ttyUSB0

Connect  
>$ picocom -b 115200 /dev/ttyUSB0 --omap crcrlf  

    picocom v3.1
    ...
    Type [C-a] [C-h] to see available commands
    Terminal ready

Check if you have AT firmware  
>AT

    OK

Check version  

>AT+GMR

    AT version:1.7.4.0(May 11 2020 19:13:04)
    SDK version:3.0.4(9532ceb)
    compile time:May 27 2020 10:12:17
    Bin version(Wroom 02):1.7.4
    OK

Exit  

>$ Ctrl+a Ctrl+x

## Communication using cu

A simple serial monitor  

>$ cu -l /dev/ttyACM0 -s 9600

Exit with ~. (tilde dot)  
