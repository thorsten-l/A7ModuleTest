# A7ModuleTest

This is a test program for the [Ai-Thinker A7](https://www.smart-prototyping.com/image/data/9_Modules/101756%20Wireless%20A6C/A6_A7_A6C_datasheet-EN.pdf) module connected to an
Arduino Pro Micro or the [Elecrow 32u4 with A7](https://www.elecrow.com/wiki/index.php?title=32u4_with_A7_GPRS/GSM) module.

## Used PINs

The pin layout is taken from the Elecrow 32u4 with A7 module.

- 4 RESET ... with the Arduino Pro Micro this pin must be connected via a N-channel MOSFET (e.g. IRLIZ44N) to the A7 reset pin.

- 5 ENABLE
- 8 PWRKEY

- 10 GPS RX software serial
- 16 GPS TX software serial (not used)


## Serial Connections

- Serial is console

- Serial1 is the hardware serial port to the A7 GSM UART

- SoftwareSerial( 10, 16 ) serial port to A7 GPS UART (RX=10, TX=16)

## Console Commands

### GPS

you can switch on and off the GPS serial port

- gps=on
- gps=off

### GSM / GPRS

- every command starting with *at* is directly send to the GSM UART

- if you like to send characters not starting with *at* start with a *'*-char as first character.

- *ctrlz* is sending a CTRL-Z char to the GSM UART

## Boot Sequence

At the program start RESET, ENABLE and PWRKEY are set to HIGH level. After 3s RESET is set to LOW level.

## Modules

- [Elecrow A7 GSM GPRS GPS Module with Mega32U4 3 In 1 Development Board ](https://aliexpress.com/item/Elecrow-Mega32U4-with-A7-GSM-GPRS-GPS-Module-A6-A6C-DIY-Kit-Newest-Development-Board-Integrated/32790443050.html)

- [Wireless Module Ai-Thinker A7 GSM GPRS GPS](https://aliexpress.com/item/Wireless-Module-A7-GSM-GPRS-GPS-3-In-1-Module-Shield-DC-5-9V-For-Arduino/32798617442.html)

- [Pro Micro ATmega32U4](https://aliexpress.com/item/Pro-Micro-ATmega32U4-5V-16MHz-Replace-ATmega328-For-Arduino-Pro-Mini-With-2-Row-Pin-Header/32808519179.html)
