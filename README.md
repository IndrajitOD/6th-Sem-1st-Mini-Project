# 🌱 Smart Plant Watering System

A 6th-semester academic mini-project for monitoring soil moisture and controlling plant irrigation using an ESP8266, soil-moisture sensor, relay, DC pump, 16×2 I2C LCD and Blynk IoT.

## Concept

```text
Soil Moisture Sensor
        ↓
     ESP8266
     ↙     ↘
 LCD       Blynk
        ↓
      Relay
        ↓
     Water Pump
        ↓
       Plant
```

The recovered software uses a **30% moisture threshold**. When the measured moisture is below the threshold in automatic mode, the pump is switched on through the relay.

## Features

- Soil-moisture monitoring
- Local LCD display
- Blynk remote monitoring
- Automatic watering
- Manual pump control through Blynk
- Relay-based pump switching

## Hardware

- ESP8266 / NodeMCU-class board
- Soil-moisture sensor/module
- Single-channel relay
- Small DC water pump
- 16×2 LCD with I2C
- Tubing
- Power source
- Prototype enclosure

Original recovered project photographs are in [`images/`](images/).

## Software

- Arduino IDE
- Arduino C/C++
- ESP8266 Arduino core
- Blynk IoT
- LiquidCrystal_I2C

## Pin Mapping

| Function | Pin |
|---|---|
| Soil moisture analog input | A0 |
| Relay control | D3 |
| LCD | I2C |
| Blynk moisture value | V0 |
| Blynk manual control | V1 |

The recovered code assumes an **active-LOW relay**: `LOW` = pump ON, `HIGH` = pump OFF.

## Repository

```text
smart-plant-watering-system/
├── README.md
├── PROJECT_STATUS.md
├── LICENSE
├── .gitignore
├── src/
│   └── smart_irrigation.ino
├── hardware/
│   ├── components.md
│   └── wiring.md
├── docs/
│   ├── system-design.md
│   └── blynk-dashboard.md
└── images/
    └── recovered prototype photographs
```

## How It Works

1. ESP8266 reads the soil-moisture sensor through A0.
2. The reading is converted to an approximate 0–100% value.
3. The percentage is shown on the LCD.
4. The percentage is sent to Blynk through V0.
5. Automatic mode compares the value with the 30% threshold.
6. If the soil is too dry, the relay activates the pump.
7. Blynk V1 provides manual pump control.

## Blynk

- **V0:** soil moisture percentage
- **V1:** manual pump control

The original Blynk screenshot was not preserved, so the repository contains documentation rather than a fabricated screenshot.

## Project Status

This is a **reconstruction of the 6th-semester academic prototype** using surviving source code, hardware photographs and project information.

The physical prototype was attempted during the semester, but the complete final working unit and some original documentation were not preserved. Therefore, this repository does not claim a verified final deployment.

No fabricated output screenshots or fabricated original circuit photographs are included.

## Calibration

The recovered implementation uses:

```cpp
map(rawValue, 0, 1023, 100, 0)
```

This is only an approximate conversion. A real deployment should calibrate the sensor using dry and wet soil readings.

## Hardware Safety

The DC pump should use an appropriate external supply and should not be driven directly from an ESP8266 GPIO. The relay/driver and power system must be selected for the pump's voltage and current requirements.

## Future Improvements

- Capacitive moisture sensor
- Water-tank level sensing
- Pump run-time protection
- Sensor calibration
- Historical moisture graphs
- Low-water notifications
- Better battery management
- Improved enclosure and waterproofing

## Academic Context

**Semester:** 6th Semester Mini Project  
**Domain:** IoT / Embedded Systems / Automation
