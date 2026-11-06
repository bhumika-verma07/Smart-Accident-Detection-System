# Smart Accident Detection & Emergency Alert System 🚗

An ESP32-based smart vehicle safety system designed to detect possible road accidents and initiate an emergency alert workflow using an MPU6050 sensor, GPS module, and GSM module.

## 📌 Project Overview

Road accidents often require immediate medical assistance. Delays in reporting accidents can increase the risk to victims.

This project aims to detect sudden changes in vehicle acceleration, alert the driver, and obtain GPS coordinates for emergency notification.

## ✨ Features

- **Accident Detection:** Uses the MPU6050 accelerometer to monitor vehicle acceleration.
- **Warning System:** Activates an LED and buzzer when a possible accident is detected.
- **Alert Cancellation:** Provides a 10-second window for the driver to cancel a false alert using a push button.
- **GPS Tracking:** Retrieves and displays latitude and longitude coordinates.
- **Emergency Alert Workflow:** Demonstrates the emergency SMS process through the Serial Monitor.

## 🛠️ Technologies & Components

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller |
| MPU6050 | Acceleration and motion sensing |
| NEO-6M GPS | Location tracking |
| SIM800L GSM | Intended for emergency SMS |
| LED | Visual warning |
| Buzzer | Audio warning |
| Push Button | Alert cancellation |
| Arduino IDE / Wokwi | Programming and simulation |

## ⚙️ Working Principle

1. The MPU6050 continuously monitors vehicle acceleration.
2. The ESP32 calculates the total acceleration magnitude.
3. If the value exceeds the configured threshold, a possible accident is detected.
4. The LED and buzzer are activated.
5. The driver gets 10 seconds to cancel the alert.
6. If the alert is not cancelled, GPS coordinates are obtained.
7. The emergency alert workflow is displayed through the Serial Monitor.

## 🔌 Pin Configuration

| Component | ESP32 Pin |
|---|---|
| MPU6050 SDA | GPIO 21 |
| MPU6050 SCL | GPIO 22 |
| LED | GPIO 25 |
| Buzzer | GPIO 26 |
| Push Button | GPIO 27 |
| GPS TX | GPIO 16 |
| GPS RX | GPIO 17 |

## 📂 Repository Structure

```text
Smart-Accident-Detection-System/
│
├── README.md
│
├── Code/
│   ├── Smart_Accident_Detection.ino
│   ├── gps-neo6m.chip.c
│   ├── gps-neo6m.chip.json
│   └── libraries.txt
│
└── Simulation/
    └── Wokwi_Project_Link.txt
```

## 🧪 Simulation

The initial prototype was developed and tested using Wokwi.

**[Run the Wokwi Simulation](https://wokwi.com/projects/476885206212803585)**

The simulation demonstrates accident detection, warning indicators, alert cancellation, GPS data parsing, and the emergency alert workflow.

## ⚠️ Current Implementation Status

- The current prototype uses simulated GPS data rather than live satellite positioning.
- The GSM emergency SMS process is currently simulated through Serial Monitor output. Real SMS transmission using the physical SIM800L module is not yet implemented.
- The acceleration threshold is a preliminary simulation value and requires calibration and physical testing.
- Physical hardware integration and real-world validation are planned as the next stage.

## 🚀 Future Scope

- Integration and testing with physical hardware.
- Real-time GPS tracking.
- Actual emergency SMS transmission using the GSM module.
- Improved accident detection through sensor calibration and filtering.
- Mobile application for monitoring and notifications.
- Integration with nearby emergency services.

## 👩‍💻 Project Details

**Project:** Smart Accident Detection & Emergency Alert System  
**Domain:** Internet of Things (IoT)  
**Controller:** ESP32  
**Simulation Platform:** Wokwi

---

*Developed as an academic mini project focused on improving vehicle safety through IoT-based accident detection and emergency alerting.*
