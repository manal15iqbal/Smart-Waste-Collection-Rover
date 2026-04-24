# Smart-Waste-Collection-Rover
Smart dustbin system that detects, classifies, and segregates waste into dry and wet categories, then autonomously moves to a larger bin and disposes collected waste using servo-based actuation and sensor feedback.

DEMO: https://drive.google.com/file/d/1jOv04suzO5tbo9p8bUJS68pQH6unGPQx/view?usp=sharing

## Overview

This project presents a smart waste management system that performs automated waste segregation, real-time bin monitoring, mobility, and self-dumping. The system is designed to reduce manual effort in waste handling and improve efficiency in urban waste collection.

The dustbin detects incoming waste, classifies it as wet or dry, stores it in separate compartments, monitors fill levels, and autonomously moves to a larger bin where it disposes the collected waste.

---

## Key Features

* Waste is detected using an ultrasonic sensor placed near the input chute
* A moisture sensor determines whether the waste is wet or dry
* A servo motor directs the waste into the corresponding compartment
* Additional ultrasonic sensors monitor bin fill levels
* A NodeMCU-based rover enables wireless movement using a mobile interface
* A tipping mechanism using an MG995 servo empties the bin into a larger container

---

## System Architecture

```
Waste Input
   ↓
Ultrasonic Detection
   ↓
Moisture Analysis
   ↓
Servo-based Segregation
   ↓
Separate Wet/Dry Bins
   ↓
Fill Level Monitoring
   ↓
Mobile Rover (Wi-Fi Controlled)
   ↓
Tipping Mechanism (Dumping)
```

---

## Hardware Components

* Arduino Uno
* NodeMCU (ESP8266)
* Ultrasonic Sensors (HC-SR04)
* Moisture Sensor
* Servo Motors (SG90, MG995)
* L298N Motor Driver
* DC Motors (for rover)
* 16x2 LCD Display
* Battery Pack

---

## Software Components

* Arduino IDE (embedded programming)
* Wi-Fi-based control interface (NodeMCU web server)
* Mobile control application (base.apk for rover movement)
* Optional image processing module (TensorFlow Lite, experimental)

---

## Results

Based on testing and observations :

* Reliable waste detection and segregation
* Accurate bin level monitoring
* Stable and repeatable tipping mechanism
* Smooth rover movement via Wi-Fi control
* Reduced oscillations and improved response time in actuation

---

## Future Improvements

* Integration of AI-based image classification for better accuracy
* IoT/cloud-based monitoring system
* Improved mechanical design for durability
* Autonomous navigation instead of manual control

---

## Conclusion

This project demonstrates a low-cost, modular, and scalable smart dustbin system capable of automated waste segregation, monitoring, mobility, and dumping. It highlights how embedded systems and sensor integration can contribute to efficient and sustainable waste management solutions.


---
