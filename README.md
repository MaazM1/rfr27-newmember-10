# RFR27 16-Channel Battery Temperature Monitor

Firmware and hardware design repository for **Project-10: 16-Channel Accumulator Temperature Monitor**, developed for Rutgers Formula Racing (RFR27).

---

## Overview

This subsystem monitors the thermal status of battery cell groups across an accumulator segment. An Arduino Nano cycles through analog channels using a multiplexer, samples conditioned temperature sensor voltages, flags over-temperature conditions, and acts as an I2C slave to report thermal data back to the vehicle's master ECU or datalogger.

* **Target Microcontroller:** Arduino Nano (ATmega328P)
* **Multiplexer:** CD74HC4067 (16:1 Analog Multiplexer)
* **Sensor Type:** Enepaq Cell Temperature Sensors (Diode/Zener Shunt)
* **Communication Interface:** I2C Slave (`0x08`)
* **Safety Threshold:** Over-temperature fault indicator active at $\ge 60^\circ\text{C}$

---

## Repository Structure

```text
├── docs/                             # Engineering design report source files (LaTeX & PDF)
├── hardware/                         # Schematics, block diagrams, and circuit documentation
└── software/
    └── temperature_monitor/          # Arduino firmware (.ino) and peripheral routines