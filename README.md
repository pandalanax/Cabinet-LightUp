# Cabinet-LightUp

![photo of circuit](https://github.com/pandalanax/Cabinet-LightUp/blob/main/media/lightup.gif)


## Components
- WS2812 Strip with 30 LEDs
- Reed Switch
- Arduino Nano 
- MCP1700 LDO 
- 2N3904 Transistor
- 1N4007 Diode
- 100NF Cap
- 2x 1µF Cap
- 1k Ohm Resistor
- 3x AA Battery
- 1 Battery Case

## Arduino Nano Modifications
After Modification, the usage of the USB port of the Nano could damage it. I program the Nano via ICSP Pins with 3.3v.

#### Core
The Core was changed to [Minicore](https://github.com/MCUdude/MiniCore). Underclocked the Nano to 8Mhz using internal oscillator. 
#### LED
Removed the Resistor for the POWER led.
#### Voltage Regulator
The nanos voltage regulator uses a lot of energy, therefore i removed the regulator and changed it to a LDO MCP1700

## Circuit
Using the transistor alone didn't help to completely shut down the WS2812 strip. Found this helpful [thread](https://forum.pjrc.com/threads/24407-Strange-WS2812-NeoPixel-backfeed-current-FYIO) which suggested using a diode to eliminate the backfeeding problem through DATA channel.

## Current Draw Measurement
The current is measured with an external Arduino Nano and INA219 Breakout Board.
![photo of current draw](https://github.com/pandalanax/Cabinet-LightUp/blob/main/media/current_consumption.png)

# TODO

- [x] add schematic
- [x] create pcb
- [ ] upload hex file to flash via avrdude 
- [ ] upload minicore settings to flash via avrdude

