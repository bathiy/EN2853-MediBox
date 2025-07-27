# 🩺 MediBox – Smart Medication Reminder System

Welcome to the **MediBox Project**, a smart embedded system developed to help users manage their daily medication intake through scheduled alarms and environmental monitoring. The project is designed and implemented using the **ESP32 microcontroller**, and it evolves across two versions:

- ✅ **Version 1** – Basic standalone system using local alarms and environment sensing.
- 🚀 **Version 2** – Advanced system with MQTT integration and remote control via Node-RED.

---

## 📂 Project Structure

| Folder | Description |
|--------|-------------|
| [`V1_MediBox`](./V1_MediBox) | Original version of MediBox built for the EN2853 Embedded Systems assignment. Uses Wi-Fi for NTP and supports 2 alarms with environment monitoring. |
| [`V2_MediBox`](./V2_MediBox) | Enhanced MediBox with MQTT communication. Publishes sensor data and receives dynamic configuration commands from a Node-RED dashboard. |

---

## 🧠 Key Features Across Versions

| Feature | Version 1 | Version 2 |
|--------|-----------|-----------|
| Real-Time Clock via NTP | ✅ | ✅ |
| Dual Alarms (with snooze) | ✅ | ✅ |
| DHT22 Sensor (Temp & Humidity) | ✅ | ✅ |
| OLED Display Interface | ✅ | ✅ |
| Button-Controlled Menu | ✅ | ✅ |
| Buzzer + LED Alerts | ✅ | ✅ |
| Light Sensing with LDR | ❌ | ✅ |
| Shade Control with Servo | ❌ | ✅ |
| MQTT Connectivity | ❌ | ✅ |
| Node-RED Dashboard Support | ❌ | ✅ |

---

## 🛠️ Technologies Used

- **Microcontroller**: ESP32
- **Simulation Platform**: [Wokwi](https://wokwi.com/)
- **Language**: C++ (Arduino)
- **Libraries**: Adafruit GFX, SSD1306, DHTesp, WiFi, PubSubClient, ESP32Servo
- **Communication**: MQTT (broker.hivemq.com)
- **Visualization**: Node-RED (for V2)

---

## 📦 Getting Started

1. Explore [`V1_MediBox`](./V1_MediBox) for a standalone version tested in Wokwi.
2. Explore [`V2_MediBox`](./V2_MediBox) for the connected version with real-time remote updates.
3. Each version contains its own detailed `README.md` file with simulation and setup instructions.

---

## 📚 Educational Context

This project was developed as part of the **EN2853 Embedded Systems** module and demonstrates core concepts such as:

- Embedded C programming
- Sensor interfacing
- Interrupt and timing logic
- Real-time system design
- IoT connectivity using MQTT
- Visual interface via Node-RED

---

## 👨‍💻 Author

**Bathiya Dissanayake**  
Electronics and Telecommunication Engineering Undergraduate  
University of Moratuwa  

---

## 🧭 Version Info

| Version | Status | Summary |
|--------|--------|---------|
| V1 | ✅ Completed | Functional simulation of MediBox on Wokwi |
| V2 | ✅ Completed | Adds MQTT + Node-RED for smart control and monitoring |

---

Thank you for exploring MediBox!  
🔗 For feedback or collaboration, feel free to open issues or fork the repo.

