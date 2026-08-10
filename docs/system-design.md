# System Design

```text
             ┌──────────────────────┐
             │ Soil Moisture Sensor  │
             └──────────┬───────────┘
                        │ Analog
                        ▼
             ┌──────────────────────┐
             │ ESP8266 / NodeMCU    │
             │                      │
             │ Read → Convert →     │
             │ Display → Control    │
             └───────┬──────┬───────┘
                     │      │
                     ▼      ▼
                   LCD    Blynk
                     │
                     ▼
                   Relay
                     │
                     ▼
                 Water Pump
                     │
                     ▼
                   Plant
```

### Automatic mode

If moisture is below the configured threshold (`30%` in the recovered code), the relay is activated and the pump turns on.

### Manual mode

Blynk V1 can request manual pump operation.

### Data flow

`Sensor → ESP8266 → moisture percentage → LCD + Blynk`

Control flow:

`ESP8266 → Relay → Pump`
