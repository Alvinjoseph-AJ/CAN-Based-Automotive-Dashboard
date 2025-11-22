# CAN-Based Automotive Dashboard

A real-time automotive dashboard using PIC microcontrollers and CAN bus communication. Three ECUs interact to monitor and transmit vehicle data including speed, RPM, gear position, engine temperature, and indicators. ECU3 acts as the dashboard unit displaying data on a CLCD with LED indicators.

---

## Project Structure

- **ECU1:** Reads analog sensors (speed and engine temperature) and transmits data over CAN.
- **ECU2:** Handles digital inputs (gear shift and indicator controls) and transmits data over CAN.
- **ECU3:** Receives CAN messages, updates CLCD display, and controls LED indicators.

---

## Features

- Real-time CAN communication between three ECUs  
- Speed, RPM, and engine temperature monitoring via ADC  
- Gear position and indicator control via digital keypad  
- CLCD dashboard display with live data  
- LED indicators for left and right turn signals  
- Timer and interrupt-based precise LED blinking  
- Modular ECU design  

---

## CAN Message IDs

| Parameter           | Message ID |
|--------------------|-----------|
| Speed               | 0x10      |
| Gear                | 0x20      |
| RPM                 | 0x30      |
| Engine Temperature  | 0x40      |
| Indicator Status    | 0x50      |

---

## Sample Dashboard Output

| SP  | G  | TM | RPM  | IN  |
|-----|----|----|------|-----|
| 65  | 3  | 90 | 2450 | ←   |

- **SP:** Speed (km/h)  
- **G:** Gear position  
- **TM:** Engine temperature (°C)  
- **RPM:** Engine revolutions per minute  
- **IN:** Indicator status (`←` Left, `→` Right, `OFF`)  

---

## Setup Instructions

1. Connect the three PIC microcontrollers via a CAN bus network.  
2. Upload the respective code for ECU1, ECU2, and ECU3.  
3. Connect the CLCD and LED indicators to ECU3.  
4. Power on the system. The dashboard will display real-time vehicle data.

---

## Usage

- Use the digital keypad to change gear; ECU3 updates gear status on CLCD.  
- Speed and engine temperature are read automatically from sensors and displayed.  
- Indicators blink LEDs and show left/right arrows on CLCD as per ECU2 input.  
- RPM is calculated from ADC readings and displayed in real-time on the dashboard.

---
