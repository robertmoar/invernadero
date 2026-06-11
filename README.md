# Invernadero 🌱
### Autonomous Greenhouse Controller — IoT + Full Stack

An ESP32-based autonomous greenhouse that monitors telemetry, controls actuators, and streams live data to a web dashboard accessible from anywhere.

Built by a DAW student learning embedded systems from the ground up — baremetal C++, cloud backend, and everything in between.

---

## Architecture

The firmware is designed for portability and testability from day one:

- **HAL (Hardware Abstraction Layer)** — separates business logic from hardware-specific code, making the codebase portable across targets
- **Digital Twin** — a native desktop build that mirrors the firmware, allowing unit tests to run on a Mac without physical hardware
- **GoogleTest suite** — validates firmware logic before flashing, with structured error handling throughout
- **Two build targets** — `env:esp32dev` for the real device, `env:native` for the desktop twin, managed by PlatformIO

```
[ ESP32 Device ]  →  [ MQTT Broker (VPS) ]  →  [ Go Backend ]  →  [ PostgreSQL ]
                                                                         ↓
                                                                  [ React Frontend ]
```

---

## Hardware

**Current:**
- [ESP32-2432S028R "CYD" — Cheap Yellow Display](https://www.aliexpress.com/item/1005004700627096.html) — main controller
- AE042 Starter Kit sensors — [Kuongshun](https://kuongshun.com/pages/tutorials)

**Incoming:**
- 12V 480LED/m 6500K grow lights
- 4-channel 12V relay module with optocoupler
- 12V 300mA water pump + 1N5822 flyback diode
- 120W 12V 10A PSU

---

## Software Stack

| Layer | Technology |
|---|---|
| Firmware | C/C++, ESP-IDF, PlatformIO |
| Testing | GoogleTest, native digital twin |
| Transport | MQTT |
| Backend | Go |
| Database | PostgreSQL |
| Frontend | React |
| Infrastructure | Docker, Nginx, Linux VPS |

---

## Project Status

**Phase 1 — Complete ✅**
- HAL foundation with GPIO abstraction
- Digital twin build environment
- PlatformIO dual-target configuration
- ESP-IDF framework integration
- GoogleTest suite with fixture-based tests

**Phase 2 — In Progress 🔧**
- Sensor implementation (temperature, humidity, soil moisture)
- MQTT telemetry pipeline
- Go backend + PostgreSQL schema
- React dashboard

---

## Running Tests

```bash
# Run firmware tests on your Mac — no hardware needed
pio test -e native
```

---

## Author

**Robert Mora** — [robertmora.dev](https://robertmora.dev)

DAW student building towards full stack embedded systems — from bare metal to browser.
Made with a lot of love and for educational purposes. Thanks for coming by 🌱