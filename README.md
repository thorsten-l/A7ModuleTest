# A7ModuleTest

This is a test program for the Ai-Thinker A7 module connected to an
Arduino Pro Micro or the Elecrow 32u4 with A7 module.

## Used PINs

The pin layout is taken from the Elecrow 32u4 with A7 module.

- 4 RESET ... with the Arduino Pro Micro this pin must be connected via a N-channel MOSFET (e.g. IRLIZ44N) to the A7 reset pin.

- 5 ENABLE
- 8 PWRKEY

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
