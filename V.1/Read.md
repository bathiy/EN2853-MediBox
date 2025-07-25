# MediBox V1 - EN2853 Assignment

This is **Version 1** of the *MediBox* project, developed as part of the **EN2853 Embedded Systems** module assignment. The system is designed to assist users with timely medicine intake by setting alarms and monitoring environmental conditions like temperature and humidity. This project is developed using **Arduino** and simulated using the **Wokwi** platform.

## 🩺 Project Overview

MediBox is a smart medicine reminder system that features:

- 🕒 Real-time clock synchronization via **NTP (Network Time Protocol)**
- ⏰ Support for **two programmable alarms** to remind medicine times
- 🌡️ Monitoring of **temperature and humidity** using a **DHT22 sensor**
- 📟 A **menu-driven user interface** with an **OLED display**
- 🚨 Buzzer and LED alerts for alarms and environment warnings
- 🔘 Simple button interface to **navigate**, **set alarms**, and **adjust settings**
- 🌐 Wi-Fi connectivity (Wokwi-GUEST) for time synchronization

## 💻 Simulation

This project is designed and tested on [Wokwi Arduino Simulator](https://wokwi.com/). All peripherals are connected virtually, including:

- **ESP32 microcontroller**
- **DHT22 sensor**
- **OLED Display (128x64)**
- **Buzzer**
- **4 Pushbuttons (UP, DOWN, OK, CANCEL)**
- **LED**

## 📁 Project Structure

- `220036L_code.ino` – Main Arduino source file with all functionality
- `README.md` – This documentation file
- `diagram.json` - Wokwi component placements describing fille
- `libraries.txt` - Related arduino libraries

## 📌 Features

| Feature | Description |
|--------|-------------|
| Set Time Zone | User can select UTC offset for accurate time |
| Set Alarm 1 & 2 | Program two separate alarms |
| View Alarms | View the currently active alarms |
| Delete Alarms | Remove existing alarms |
| Snooze Function | Option to snooze alarm for 5 minutes |
| Environmental Alerts | Alerts when temp/humidity exceed safe range |

## 🛠️ Libraries Used

- [`Adafruit_GFX`](https://github.com/adafruit/Adafruit-GFX-Library)
- [`Adafruit_SSD1306`](https://github.com/adafruit/Adafruit_SSD1306)
- [`DHTesp`](https://github.com/beegee-tokyo/DHTesp)

Install these libraries using Arduino Library Manager or add them to your Wokwi project.

## 🔧 Controls

- **UP (GPIO 32)**: Navigate menu up / Increase value
- **DOWN (GPIO 35)**: Navigate menu down / Decrease value
- **OK (GPIO 33)**: Select / Confirm
- **CANCEL (GPIO 27)**: Exit or cancel current action

## 📊 Display

The OLED display shows:

- Current time and date
- Menu navigation
- Alarm setting prompts
- Environmental status messages

## 🔔 Alerts

- **Buzzer** plays a melody to indicate alarms or environment warnings.
- **LED** turns on during active alarms.


## ✅ How to Run on Wokwi

1. Visit [Wokwi Project Simulator](https://wokwi.com/)
2. Upload the `.ino` file and required libraries
3. Set up the virtual connections:
   - Connect DHT22 to GPIO 13
   - OLED I2C to SDA (GPIO 21) and SCL (GPIO 22)
   - Buttons and buzzer to respective pins
4. Start simulation and interact using virtual buttons

## 📚 EN2853 Module

This project was submitted for the **EN2853 Embedded Systems** module. It demonstrates:

- Hardware-software co-design
- Real-time clock use with Wi-Fi
- Embedded environmental sensing
- State machine-based menu navigation

---

**Developed by:** *Bathiya Prabhath Anuradha 220036L *  
**Version:** 1.0  
**Module:** EN2853  
**Platform:** Arduino (ESP32) + Wokwi  
**Simulation:** [Wokwi.com](https://wokwi.com/projects/426498239432179713)

