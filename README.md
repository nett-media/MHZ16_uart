# MHZ16_uart

Arduino IDE library for the MH-Z16 CO₂ sensor. Tested with ESP32 but might just work for Arduino too.

Version 0.1

## Credits and License

Based on: 
* https://github.com/IntarBV/MHZ16_uart and
* https://github.com/nara256/mhz19_uart

License: MIT

### Motivation

i had runtime warnings because Serial Interface is created at every reading (HardwareSerial hserial(_serialno);`) and some possible overlapping callbacks..
Thats why i hacked this quick and dirty version..

## Usage

1. Add this library to your Arduino IDE's libraries folder.
1. Include the library in your program
1. Connect your MH-Z16 sensor to your ESP32

    MH-Z16 Vcc to 5V power supply  
    MH-Z16 GND  to common GND  
    MH-Z16 Tx   to ESP32 GPIO pin to use as _Rx_  
    MH-Z16 Rx   to ESP32 GPIO pin to use as _Tx_  
    Other MH-Z16 pins are not supported
1. Upload your program to the ESP32



## MH-Z16 Datasheet

<http://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z16%20CO2%20V2.1.pdf>

## Change log

* convert from c++ class to c functions