# Wiring Documentation

The complete original circuit diagram was not preserved. This file therefore records only connections supported by the recovered source code.

| Device | Connection |
|---|---|
| Soil moisture analog output | ESP8266 A0 |
| Relay input | ESP8266 D3 |
| LCD | I2C |
| Blynk moisture value | V0 |
| Blynk manual control | V1 |

The LCD address in the recovered code is `0x27`.

The relay is assumed to be active LOW:

```text
LOW  = pump ON
HIGH = pump OFF
```

The pump should be powered through an appropriate external supply and switched through the relay, not directly from an ESP8266 GPIO.

Because the original final wiring diagram is unavailable, this is intentionally documented as a **reconstructed reference**, not the original historical circuit diagram.
