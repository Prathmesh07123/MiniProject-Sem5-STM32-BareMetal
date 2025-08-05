# 📚 Week 2 – Component Research

This document summarizes research done on the hardware modules selected for Semester 5 of the project: **Cow Birthing Alert, Fall Detection & GPS Geofencing System**.

---

## 1️⃣ GPS Module – NEO-6M

- **Purpose:** Tracks the real-time location of the cow.
- **Interface:** UART (Default baud rate: 9600 bps)
- **Operating Voltage:** 3.3V to 5V (with onboard regulator)
- **Update Rate:** 1 Hz (default), can go up to 5 Hz
- **Accuracy:** ~2.5m CEP
- **Reason for Selection:**
  - Easily available
  - Compatible with STM32F103RB UART
  - Low power and rural-ready
- **Datasheet:** [u-blox NEO-6M PDF](https://www.u-blox.com/sites/default/files/NEO-6_DataSheet_%28GPS.G6-HW-09005%29.pdf)

---

## 2️⃣ IMU Sensor – MPU6050

- **Purpose:** Detect motion, sudden falls, and abnormal movements
- **Interface:** SPI
- **Operating Voltage:** 3.3V
- **Features:**
  - 3-axis accelerometer + 3-axis gyroscope
  - Digital Motion Processor (DMP)
- **Reason for Selection:**
  - Stable I2C/SPI protocol
  - Available libraries and example code
  - Can detect falls and orientation change
- **Datasheet:** [MPU6050 Register Map](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)

---

## 3️⃣ LoRa Module – SX1278 (Ra-02)

- **Purpose:** Long-range communication between wearable node and base station (no internet required)
- **Interface:** UART or SPI (we prefer SPI for fast communication)
- **Frequency:** 433 MHz
- **Range:** Up to 5–10 km in open field (ideal for rural farms)
- **Operating Voltage:** 3.3V (⚠️ Use logic level converter if needed)
- **Reason for Selection:**
  - High range for low-power applications
  - Works in unlicensed band
  - Well-supported by STM32
- **Datasheet:** [SX1278 LoRa PDF](https://www.semtech.com/uploads/documents/sx1276.pdf)

---

## 4️⃣ Temperature Sensor – DHT11

- **Purpose:** Monitor cow’s body temperature
- **Interface:** Single-wire digital GPIO
- **Operating Voltage:** 3.3V – 5V
- **Accuracy:** ±2°C, Range: 0–50°C
- **Reason for Selection:**
  - Simple to interface/Required precise delay
  - Adequate for animal surface temp
  - Supported with timing-based read code (bare-metal)
- **Datasheet:** [DHT11 PDF](https://www.electronicwings.com/public/images/user_images/images/dht11.pdf)

---

### 5️⃣ ESP8266 Wi-Fi Module

- **Purpose:** Enables cloud communication from the STM32 receiver to **ThingSpeak**
- **Interface:** SPI (via AT commands with STM32L4P5ZG)
- **Operating Voltage:** 3.0V – 3.6V  
- **Wi-Fi Standard:** 802.11 b/g/n  
- **Use in Project:**  
  - Mounted on the **receiver side**
  - Transfers sensor data (received via LoRa) to **ThingSpeak Cloud**
  - Communicates using **AT commands** over SPI
- **Datasheet:** [ESP8266 AT Command Set (PDF)](https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf)
---

## ⚙️ Optional Components 

---

## ❤️ Pulse Sensor – MAX30102

- **Purpose:** Measures cow’s heart rate using optical sensing
- **Interface:** I²C  
- **Operating Voltage:** 1.8V (core), 3.3V (I/O)
- **Use in Project:**  
  - Helps monitor animal health during birthing or stress
- **Challenges:**    
  - Requires filtering and signal tuning
- **Status:** Optional – Will be tested for reliability in field conditions
- **Datasheet:** [MAX30102 PDF](https://datasheets.maximintegrated.com/en/ds/MAX30102.pdf)


---

> ✅ This research helped in selecting modules that are **power-efficient**, **easy to interface with STM32 (bare-metal)**, and **rural environment-friendly**.

