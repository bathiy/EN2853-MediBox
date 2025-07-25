# MediBox V2 – Smart Medication Reminder with MQTT & Node-RED

MediBox V2 is a smart IoT-based medication reminder and environment monitor system built using an **ESP32** microcontroller. It helps users manage medication schedules by triggering alarms and also monitors **temperature**, **humidity**, and **light intensity**. This version integrates **MQTT protocol** to communicate with **Node-RED**, enabling real-time monitoring and control.

---

## 🚀 Features

- ⏰ **Dual Alarm System** – Set up to two daily medication alarms with snooze functionality.
- 🌡️ **Environment Monitoring** – Tracks temperature and humidity using a DHT22 sensor.
- 💡 **Light Intensity Monitoring** – Measures light using an LDR, averages readings, and publishes via MQTT.
- 🌐 **Wi-Fi Connectivity** – Connects to an NTP server to sync time and MQTT broker for data publishing.
- 🕒 **Time Zone Configuration** – Manually set your UTC time zone offset.
- 🔊 **Audio-Visual Alerts** – Alarm triggers a buzzer and LED; cancel/snooze via push buttons.
- 🪟 **Shade Control** – Adjusts servo-based shading system based on environment and light conditions.
- 📡 **MQTT Integration** – Publishes environmental data and receives real-time configuration updates (ts, tu, gama, etc.)
- 🧠 **Node-RED Dashboard** – Control and visualize MediBox data through an intuitive Node-RED UI.

---

## 🛠️ Hardware Components

- ESP32 Dev Board
- OLED Display (SSD1306)
- DHT22 Sensor
- LDR (Light-Dependent Resistor)
- Servo Motor
- Buzzer
- Push Buttons (OK, Cancel, Up, Down)
- LED Indicator
- Wi-Fi Network Access

---

## 📦 Libraries Used

- `WiFi.h`
- `Wire.h`
- `PubSubClient.h` – For MQTT communication
- `Adafruit_GFX.h`, `Adafruit_SSD1306.h` – OLED display
- `DHTesp.h` – DHT sensor interface
- `ESP32Servo.h` – Servo motor control

---

## 🧪 MQTT Topics

| Topic        | Direction | Description                              |
|--------------|-----------|------------------------------------------|
| `Average_LDR` | Publish   | Sends average light intensity            |
| `Temperature` | Publish   | Sends current temperature reading        |
| `ts`         | Subscribe | Sample interval for LDR (in ms)          |
| `tu`         | Subscribe | Averaging interval for LDR (in ms)       |
| `Theta_off`  | Subscribe | Minimum angle offset for servo shading   |
| `gama`       | Subscribe | Gain parameter for shading calculation   |
| `T_med`      | Subscribe | Reference temperature for servo control  |

Broker used: `broker.hivemq.com`

---

## 🌍 Node-RED Integration

To visualize and control the MediBox:

1. **Connect to the MQTT broker** (`broker.hivemq.com`) using MQTT-in and MQTT-out nodes.
2. Subscribe to the respective topics to receive data (`Average_LDR`, `Temperature`).
3. Use MQTT-out nodes to send updates to topics like `ts`, `tu`, `gama`, etc.
4. Design a dashboard with sliders/inputs to modify the values dynamically and buttons to trigger system changes.
5. Optionally, log data to a database or visualize using graphs.

---

## 🧰 Setup Instructions

1. **Connect all components** to the ESP32 as defined in pin configuration.
2. **Upload the sketch** to your ESP32 using the Arduino IDE.
3. Open the serial monitor to verify successful Wi-Fi and MQTT connections.
4. Use the onboard buttons to set alarms and time zone.
5. Launch your Node-RED dashboard and configure MQTT nodes to subscribe/publish to relevant topics.

---

## 🔧 Key Functions

- `set_time_zone()` – Manually adjust UTC offset.
- `set_alarm()` – Set alarm hour and minute.
- `alarm_ring()` – Buzzer + LED activation and snooze/stop options.
- `check_temp()` – Warns when temperature or humidity is out of healthy range.
- `getAverageLightIntensity()` – Samples and averages LDR readings.
- `shadeControl()` – Calculates servo angle using received parameters and publishes data.

---

## 🧠 How It Works

- The ESP32 connects to Wi-Fi and synchronizes time via NTP.
- Every `ts` milliseconds, it samples the LDR value and computes an average every `tu` milliseconds.
- MQTT messages from Node-RED allow remote reconfiguration of timing and shading behavior.
- Alarms trigger audible and visual alerts. The user can snooze or cancel alarms.
- Shade control uses a mathematical model based on average light, temperature, and user-defined parameters to adjust a servo.

---
**Developed by:** *Bathiya Prabhath Anuradha 220036L *  
**Version:** 1.0  
**Module:** EN2853  
**Platform:** Arduino (ESP32) + Wokwi  
**Simulation:** [Wokwi.com](https://wokwi.com/projects/431290141517189121)
