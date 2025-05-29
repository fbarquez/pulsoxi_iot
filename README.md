
# Development of a Microcontroller-Based Pulse Oximeter with Wireless Data Transmission

![Status](https://img.shields.io/badge/status-completed-brightgreen)
![License](https://img.shields.io/badge/license-Unlicensed-red)
![Language](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Microcontroller-orange)
![IoT](https://img.shields.io/badge/IoT-ThingSpeak-blue)
![Firmware](https://img.shields.io/badge/Firmware-MPLAB%20X-lightblue)
![UI](https://img.shields.io/badge/UI-GitHub%20Pages-lightgrey)
![Project Type](https://img.shields.io/badge/Type-Bachelor%20Thesis-yellow)
![Device](https://img.shields.io/badge/Device-PIC16F1936-blueviolet)


---

## Project Overview

This repository documents the development of a **microcontroller-based pulse oximeter** that leverages wireless data transmission via Wi-Fi for remote health monitoring. It was developed as part of a Bachelor’s thesis in **Information and Communication Technology Engineering** at HTW Berlin.

The system measures **SpO₂ (blood oxygen saturation)** and **BPM (heart rate)** using optical sensors, processes the signals through analog conditioning and a **PIC16F1936 microcontroller**, displays them on an LCD, and sends the data to the **ThingSpeak IoT platform** using an ESP32-C6 module.

---

🔗 **Multilingual interactive web presentation:**  
👉 [Visit the Project Website](https://yourusername.github.io/SpO2-Monitor-Project/)

---

## 📑 Table of Contents

- [System Description](#system-description)
- [Architecture Overview](#architecture-overview)
- [Hardware Design](#hardware-design)
- [Firmware and Software](#firmware-and-software)
- [Data Transmission and Visualization](#data-transmission-and-visualization)
- [Folder Structure](#folder-structure)
- [Usage Instructions](#usage-instructions)
- [License & Notices](#license--notices)

---

## System Description

The system is built to detect heart rate and SpO₂ levels using a **transmitter-receiver optical sensor arrangement**. The analog signal undergoes conditioning (filtering and amplification), is digitized using a PIC16F1937 microcontroller, and then transmitted via UART to an ESP32 module, which finally uploads the data to the **ThingSpeak IoT platform** over WiFi.

This implementation follows a modular approach separating:

- **Sensor input and analog conditioning**
- **Signal digitization and data processing**
- **Wireless transmission and data visualization**

---

## Architecture Overview

The complete system is split into three main modules:

1. **Analog Front-End (AFE)**:
   - Sensor: IR LED and BPW34 photodiode
   - Signal conditioning: low-pass & high-pass filters, current-to-voltage converter, non-inverting amplifier

2. **Microcontroller Unit (MCU)**:
   - PIC16F1937 with ADC to digitize signals
   - UART communication with ESP32

3. **Connectivity & Visualization**:
   - ESP32 C6 receives UART data
   - Sends it to ThingSpeak cloud server
   - Real-time data charts shown on the dashboard

Diagrams of this architecture can be found in the `images/` folder and on the web version.

---

## Hardware Design

Schematic design and PCB layouts were made using **EAGLE**. The hardware is modular and comprises:

- Pulse sensor circuits for both RED and IR light
- Custom-designed PCBs for:
  - Signal conditioning
  - Power regulation
  - Sensor connection
- 16x2 LCD display for real-time visualization

The `hardware/` folder contains:
- `.sch` and `.brd` files for Eagle
- PDF exports for quick access
- Rendered PCB previews (top, bottom, drill)

---

## Firmware and Software

### PIC16F1937 Firmware

- Written in C using MPLAB X IDE and MCC (Microchip Code Configurator)
- Core features:
  - ADC configuration for analog signals
  - UART communication setup
  - Data formatting and LCD update

See: `firmware/SpO2_Oximetro_Calculo/`

### ESP32 UART Receiver

- Programmed using Arduino Framework
- Parses UART data from PIC
- Establishes WiFi connection and sends data to ThingSpeak

See: `software/USART_Receptor_WIFI/USART_Receptor_WIFI.ino`

---

## Data Transmission and Visualization

- Platform: [ThingSpeak](https://thingspeak.com)
- Two data fields:
  - SpO₂ (%)
  - Heart Rate (bpm)
- Real-time data graphs
- Dashboard view available for sharing and monitoring

---

## Folder Structure

```
.
├── docs/
├── firmware/
├── hardware/
├── images/
├── software/
├── assets/
├── README.md
├── NOTICE.md
├── LICENSE
└── requirements.md
```

---

## Usage Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/SpO2-Monitor-Project.git
   cd SpO2-Monitor-Project
   ```

2. Open the firmware in MPLAB X:
   - Build and flash to PIC16F1937

3. Load the ESP32 `.ino` code in Arduino IDE and upload

4. Open your [ThingSpeak channel](https://thingspeak.com) and configure it to receive data

5. Check real-time values either via:
   - 16x2 LCD
   - ThingSpeak dashboard

---

## Demonstration Video

 [Watch the live demo on Dropbox](https://www.dropbox.com/scl/fi/jzmq0wq67i9w6cfi0vw9p/FernandoBarrigaVasquez_videodesProjekts.mp4?rlkey=ytrc685q6z3rqatgajav5w1xa&st=frvmd6lj&dl=0)

---

## License & Notices

This project is **not licensed** for reuse, redistribution, or modification.

> **Copyright © 2024 Fbarquez**

Permission is **not granted** to use, copy, modify, merge, publish, distribute, sublicense, or sell copies of this software.

This repository is provided strictly for **educational and demonstrational purposes** only.

See [LICENSE](LICENSE) for full legal information.
