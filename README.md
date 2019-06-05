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

1. Install the Arduino IDE (version 1.8.8+): https://www.arduino.cc/en/Main/Software
2. Install the serial driver for the ESP-12F Wi-Fi chip: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
3. In the Arduino IDE, go to Preferences and set the "Additional Board Managers" URLs to http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Install esp8266 support: Tools | Board | Board Manager
    - esp8266 by ESP8266 Community 2.4.2
5. Install the required modules: Sketch | Include Libraries | Manage Libraries
    - GxEPD2 by Jean-Marc Zingg version 1.1.0
    - Adafruit GFX Library by Adafruit 1.4.8
6. Under Tools set the following settings:
    - Board: "Generic ESP8266 Module"
    - Upload Speed "115200"
    - CPU Frequency: "80 MHz"
    - Crystal Frequency: "26 MHz"
    - Flash Size: "4M (3M SPIFFS)"
    - Flash Mode: "DIO"
    - Flash Frequency: "40MHz"
    - Reset Method: "nodemcu"
    - Debug port: "Disabled"
    - Debug Level: "None"
    - IwIP Variant: "v2 Lower Memory"
    - VTables: "Flash"
    - Exceptions: "Disabled"
    - Builtin Led: "2"
    - Erase Flash: "Only Sketch"
    - Espressif FW: "nonos-sdk 2.2.1 (legacy)"
    - SSL support: "All SSL chipers (most compatible)"
    - Port: "Serial port /dev/cu.SLAB_USBtoUART" (will be selected automatically)
    - Programmer: "ArduinoISP"
7.  Open the speakerbadge.ino sketch
    - File | Open | codecard.ino
8. Connect the CodeCard via USB to your computer
9. Establish serial connection via Arduino IDE:
    - Tools | Serial Monitor
10. Turn on the Code Card
11. From the Arduino IDE choose Sketch | Upload
    - The Arduino IDE may compile the skectch before uploading to the Code Card.
    - The following output indicates completed firmware upload:
```
Sketch uses 281556 bytes (26%) of program storage space. Maximum is 1044464 bytes.
Global variables use 32724 bytes (39%) of dynamic memory, leaving 49196 bytes for local variables. Maximum is 81920 bytes.
esptool.py v2.6
2.6
esptool.py v2.6
Serial port /dev/cu.SLAB_USBtoUART
Connecting........_
Chip is ESP8266EX
Features: WiFi
MAC: 3c:71:bf:2d:83:22
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Auto-detected Flash size: 4MB
Compressed 285712 bytes to 207146...

Writing at 0x00000000... (7 %)
Writing at 0x00004000... (15 %)
Writing at 0x00008000... (23 %)
Writing at 0x0000c000... (30 %)
Writing at 0x00010000... (38 %)
Writing at 0x00014000... (46 %)
Writing at 0x00018000... (53 %)
Writing at 0x0001c000... (61 %)
Writing at 0x00020000... (69 %)
Writing at 0x00024000... (76 %)
Writing at 0x00028000... (84 %)
Writing at 0x0002c000... (92 %)
Writing at 0x00030000... (100 %)
Wrote 285712 bytes (207146 compressed) at 0x00000000 in 18.2 seconds (effective 125.4 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```
