# RFR27 16-Channel Battery Temperature Monitor

Firmware and hardware files for **Group-10: 16-Channel Temperature Monitor**, built for Rutgers Formula Racing (RFR27).

---

## Overview

This board reads 8 channel temperatures using an Arduino Nano and a CD74HC4067 multiplexer. The firmware cycles through each channel, converts the analog voltages from the Enepaq temperature sensors into degrees Celsius, and checks for any cells running over 60°C. If a cell passes the limit, it trips the onboard fault LED. The Nano also runs as an I2C slave (`0x08`) so the master can pull the average, min, and max segment temperatures on request.

- **MCU:** Arduino Nano (ATmega328P)
- **Multiplexer:** CD74HC4067 (16:1 Analog MUX)
- **Sensors:** Enepaq Cell Temperature Sensors
- **Comms:** I2C Slave (`0x08`)
- **Fault Limit:** >= 60°C

---

## Repository Structure

```text
├── docs/                             # Design document source files (LaTeX & PDF)
├── hardware/                         # Schematics and revisions 
└── software/
    └── temperature_monitor/          # Arduino code
```
