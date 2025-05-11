# minecu
A minimal Arduino-based Engine Control Unit (ECU) prototype that simulates RPM sensing and ignition timing logic for testing purposes.

## Simple Arduino-Based ECU Prototype

This project is a basic simulation of an Engine Control Unit (ECU) using an Arduino. It measures engine RPM from a crankshaft sensor (like a Hall effect sensor), calculates timing, and triggers ignition pulses accordingly. Designed for engine labs or embedded systems experimentation.

---

## Features

- Real-time RPM measurement via crankshaft sensor (Hall effect or IR)
- Simulated ignition trigger based on RPM
- Serial output for RPM data logging
- Expandable for throttle input, injector control, or engine temp sensors

---

## Requirements

| Component | Description |
|----------|-------------|
| Arduino Uno / Nano | Main microcontroller |
| Hall sensor / Encoder | RPM input (crankshaft pulse) |
| LED / MOSFET & Coil | Simulated ignition output |
| Breadboard + Wires | Circuit building |
| (Optional) Potentiometer / Thermistor | Throttle or temp simulation |
| (Optional) fzf / OLED Display | For real-time feedback |

---

## Wiring Overview

| Pin | Connected To | Purpose |
|-----|--------------|---------|
| D2  | Hall Sensor Output | Interrupt for RPM |
| D8  | LED / Ignition Sim | Digital ignition signal |

> NOTE: Use `attachInterrupt()` on pin D2 for RPM detection.

---

## Code Overview

- Interrupt captures crankshaft pulses
- Every second, RPM is calculated and printed
- A digital pulse is sent to simulate ignition timing

```cpp
attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING);
rpm = (pulseCount / 2.0) * 60;
digitalWrite(8, HIGH); delay(10); digitalWrite(8, LOW);
```
## Setup
`git clone https://github.com/yourusername/arduino-simple-ecu.git`
`cd arduino-simple-ecu`

- Open the `.ino` file in the Arduino IDE
- Upload to an Arduino Uno/Nano
- Open Serial Monitor to see live RPM
- Trigger pulses via crank sensor to test

## Future Add-ons
- Injector pulse logic with PWM
- MAP/MAF sensor simulation
- Fuel/ignition lookup table (2D map)
- OLED screen or UART display for telemetry
