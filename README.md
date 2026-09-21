# Smart Wheelchair

An Arduino-based assistive mobility prototype designed to improve
user-controlled mobility and obstacle awareness.

## Project Overview

This project combines mechanical design, electronics, embedded
programming, sensors, motor control, and Bluetooth communication
to develop a functional wheelchair prototype.

## Key Features

- Joystick-based movement control
- Bluetooth control
- Ultrasonic obstacle detection
- IR obstacle detection
- Adaptive motor speed control
- Buzzer-based proximity warning
- Emergency stop mechanism
- Battery voltage monitoring

## Hardware

- Arduino
- Motor driver
- DC motors
- Ultrasonic sensor
- IR sensors
- HC-05 Bluetooth module
- KY-023 joystick
- 12V battery
- Battery indicator
- Buzzer
- Emergency stop switch

## Arduino Pin Connections

### Digital Pins

| Arduino Pin | Connection | Function |
|---|---|---|
| 13 | Left IR sensor | Detects an obstacle on the left/front side |
| 12 | Right IR sensor | Detects an obstacle on the right/front side |
| 11 | Motor driver input 1 | Motor control input |
| 10 | Ultrasonic TRIG | Ultrasonic sensor trigger pin |
| 9 | Motor driver input 3 | Motor control input |
| 8 | Ultrasonic ECHO | Ultrasonic sensor echo pin |
| 7 | Motor driver input 2 | Motor control input |
| 6 | Buzzer | Audible proximity/safety alert |
| 5 | Motor driver input 4 | Motor control input |
| 4 | HC-05 STATE | Bluetooth module state/status pin |
| 1 | HC-05 RX | Bluetooth serial receive |
| 0 | HC-05 TX | Bluetooth serial transmit |

### Analog Pins

| Arduino Pin | Connection | Function |
|---|---|---|
| A0 | KY-023 joystick X-axis | Horizontal joystick movement |
| A1 | KY-023 joystick Y-axis | Vertical joystick movement |
| A2 | Joystick switch (SW) | Joystick push-button/switch input |

## Bluetooth Control

The wheelchair can also be controlled wirelessly using an HC-05
Bluetooth module. The following commands are mapped to movement
functions:

| Command | Action | Description |
|---|---|---|
| `w` | Forward | Move the wheelchair forward |
| `a` | Right | Turn/move right |
| `d` | Left | Turn/move left |
| `s` | Reverse | Move backward |
| `x` | Temporary stop | Temporarily stop movement |

## Engineering Challenges

### Structural Stability

...

### Joystick Mounting

...

### Battery Monitoring

...

## Development Journal

The complete project journal documents the development process,
including design decisions, hardware integration, testing,
challenges encountered, and prototype development.

📘 **[View Complete Project Journal](https://docs.google.com/document/d/1CIjM_xLYNCckEMdnfBFI1WbFrF81M3wR/edit?usp=drive_link&ouid=100130635653822734064&rtpof=true&sd=true)**

## Future Improvements

...
