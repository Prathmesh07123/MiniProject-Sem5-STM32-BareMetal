# Week 2 – Interface Plan

## ✅ Goals
- Define communication protocols between STM32 boards and hardware modules.
- Plan pin assignments and signal routing.
- Establish interface methods for sensor data acquisition and wireless communication.

---

## 1️⃣ Communication Protocols

| Module           | Interface | Notes                          |
|------------------|-----------|--------------------------------|
| GPS (NEO-6M)     | UART      | Default baud rate 9600 bps      |
| IMU (MPU6050)    | SPI       | For fast, stable sensor reading |
| LoRa (SX1278)    | SPI       | Preferred over UART for speed   |
| Temperature (DHT11) | GPIO     | Single-wire digital interface   |
| Pulse Sensor (MAX30102) | I2C  | Standard two-wire communication |
| Wi-Fi (ESP8266)  | SPI       | AT commands via SPI on STM32    |

---

## 2️⃣ Pin Mapping Strategy

- Use dedicated UART pins for GPS communication.
- SPI bus shared between IMU and LoRa with separate Chip Select (CS) lines.
- GPIO pins reserved for DHT11 data line.
- I2C pins allocated for Pulse Sensor.
- Assign interrupts where applicable (e.g., IMU data ready).
- Keep power supply and ground lines well-planned to minimize noise.

---

## 3️⃣ Interface Considerations

- Use logic level converters where voltage mismatches occur (e.g., LoRa and ESP8266 require 3.3V).
- Prioritize SPI bus speed and minimize conflicts with careful CS control.
- Ensure UART baud rates are consistent with module specifications.
- Implement software debouncing and timing for DHT11 sensor reads.
- Plan for interrupt-driven data acquisition where possible to reduce CPU load.

---

## 4️⃣ Next Steps

- Finalize detailed pin assignments and routing.
- Begin schematic capture and PCB layout based on interface plan.
- Develop initial bare-metal drivers for SPI and UART communications.
