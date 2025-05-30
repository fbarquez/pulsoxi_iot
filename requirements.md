# Project Requirements

This document lists all the tools, libraries, and platforms required to build, upload, and run the Pulse Oximeter project.

---

## Hardware Requirements

- **Microcontroller**: PIC16F1937
- **Wi-Fi Module**: ESP32-C6
- **Sensors**:
  - BPW34 photodiode
  - IR and RED LEDs
- **Display**: 16x2 LCD (HD44780 compatible)

---

## Development Tools

### For PIC16F1937 (Firmware)

- [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide) (v6.0 or later)
- [MPLAB XC8 Compiler](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers) (v2.40 or later)
- [MCC - MPLAB Code Configurator](https://www.microchip.com/mplab/mplab-code-configurator)

### For ESP32 (Wi-Fi Transmitter)

- [Arduino IDE](https://www.arduino.cc/en/software) (v2.0 or later)
- ESP32 Board Support via Board Manager  
  (Install via: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`)
- Required Arduino libraries:
  - `WiFi.h`
  - `HTTPClient.h`

---

## Hardware Design

- [Autodesk EAGLE](https://www.autodesk.com/products/eagle/overview) (v9.6 or later)

---

## Online Services

- [ThingSpeak](https://thingspeak.com) IoT platform
  - One channel with at least 2 fields: SpO₂ and BPM
  - Optional: API Key for write access

- [GitHub Pages](https://pages.github.com/) for hosting the presentation page (optional)

---

## Optional Tools

- [Proteus / LTspice / Falstad] (for circuit simulation if used during development)
- [Markdown Preview](https://marketplace.visualstudio.com/items?itemName=shd101wyy.markdown-preview-enhanced) (for README visualization)

---

## Notes

- Ensure all USB drivers for PICkit or ESP32 are properly installed.
- Internet access is required for data upload to ThingSpeak.

