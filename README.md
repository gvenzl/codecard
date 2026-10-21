# Code Card

Code repository for Arduino Code Card.

The code card runs a [ESP8266](https://en.wikipedia.org/wiki/ESP8266) Wi-fi microcontroller chip.

The ESP8266 low-cost Wi-Fi microchip comes with full TCP/IP stack and microcontroller capability, produced by manufacturer Espressif Systems.  
The processor is an L106 32-bit RISC microprocessor core running at 80 MHz, with 4 MiB external QSPI flash. The ESP8266 supports IEEE 802.11 b/g/n Wi-Fi, WEP or WPA/WPA2 authentication, and also supports open networks.

### Software

In order to customise the Code Card firmware, you need to download the [Arduino IDE](https://www.arduino.cc/en/Main/Software) and configure it to use the Arduino core for ESP8266 WiFi chip.  
The Arduino core for ESP8266 is a C++ based firmware. With this core, the ESP8266 CPU and its Wi-Fi components can be programmed like any other Arduino device using the Arduino IDE.

## Instructions

The following instruction describes the setup and configuration of the Arduino IDE, and the process to upload firmware to your Code Card using the Arduino IDE:

1. Install the Arduino IDE (version 2.3.10+): https://www.arduino.cc/en/Main/Software
2. Install the serial driver for the ESP-12F Wi-Fi chip: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
3. In the Arduino IDE, go to Preferences and set the "Additional Board Managers" URLs to http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Install esp8266 support: Tools | Board | Board Manager
   - esp8266 by ESP8266 Community 3.1.2
5. Install the required modules: Sketch | Include Libraries | Manage Libraries
   - GxEPD2 by Jean-Marc Zingg version 1.6.9
   - Adafruit GFX Library by Adafruit 1.13.0
6. Under Tools set the following settings:
   - Board: "Generic ESP8266 Module"
   - Upload Speed "115200"
   - CPU Frequency: "80 MHz"
   - Crystal Frequency: "26 MHz"
   - Flash Size: "4M (FS:3M OTA:~512KB)"
   - Flash Mode: "DIO"
   - Flash Frequency: "40MHz"
   - Reset Method: "dtr (aka nodemcu)"
   - Debug Level: "None"
   - IwIP Variant: "v2 Lower Memory"
   - VTables: "Flash"
   - Builtin Led: "2"
   - Erase Flash: "Only Sketch"
   - Port: "Serial port /dev/cu.usbserial-018DC235" (will be selected automatically)
7. Open the speakerbadge.ino sketch
   - File | Open | codecard.ino
8. Connect the CodeCard via USB to your computer
9. Establish serial connection via Arduino IDE:
   - Tools | Serial Monitor (115200 baud)
10. Turn on the Code Card
11. From the Arduino IDE choose Sketch | Upload
    - The Arduino IDE may compile the skectch before uploading to the Code Card.
    - The following output indicates completed firmware upload:

```
. Variables and constants in RAM (global, static), used 35492 / 80192 bytes (44%)
║   SEGMENT  BYTES    DESCRIPTION
╠══ DATA     1496     initialized variables
╠══ RODATA   1324     constants
╚══ BSS      32672    zeroed variables
. Instruction RAM (IRAM_ATTR, ICACHE_RAM_ATTR), used 60343 / 65536 bytes (92%)
║   SEGMENT  BYTES    DESCRIPTION
╠══ ICACHE   32768    reserved space for flash instruction cache
╚══ IRAM     27575    code in IRAM
. Code in flash (default, ICACHE_FLASH_ATTR), used 287740 / 1048576 bytes (27%)
║   SEGMENT  BYTES    DESCRIPTION
╚══ IROM     287740   code in flash
esptool.py v3.0
Serial port /dev/cu.usbserial-018DC235
Connecting....
Chip is ESP8266EX
Features: WiFi
Crystal is 26MHz
MAC: 3c:71:bf:2d:83:22
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Auto-detected Flash size: 4MB
Compressed 322288 bytes to 224190...
Writing at 0x00000000... (7 %)
Writing at 0x00004000... (14 %)
Writing at 0x00008000... (21 %)
Writing at 0x0000c000... (28 %)
Writing at 0x00010000... (35 %)
Writing at 0x00014000... (42 %)
Writing at 0x00018000... (50 %)
Writing at 0x0001c000... (57 %)
Writing at 0x00020000... (64 %)
Writing at 0x00024000... (71 %)
Writing at 0x00028000... (78 %)
Writing at 0x0002c000... (85 %)
Writing at 0x00030000... (92 %)
Writing at 0x00034000... (100 %)
Wrote 322288 bytes (224190 compressed) at 0x00000000 in 19.7 seconds (effective 130.7 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```
