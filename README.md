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

During the construction of the wheelchair, I initially found that
the backrest was not remaining firmly in position. This affected the
overall structural stability and made the prototype less durable.

To address this, I reinforced the connection between the support
structure and the backrest from the outside of the wheelchair using
additional tape. This helped prevent unwanted movement and kept the
backrest and supporting structure securely aligned.

The structural supports were also gradually trimmed during
construction to correct uneven heights and improve the overall
stability of the prototype.

### Joystick Mounting

A major challenge was finding a mounting structure that could
withstand the repeated force applied when a user operates the
joystick. The initial mounting options were not sufficiently rigid
for reliable operation.

To solve this, I designed a custom support using a cardboard base
for the joystick and a cardboard pillar underneath it. The joystick
base was secured using tape and reinforced with a hot glue gun to
increase the rigidity and durability of the mounting.

This allowed the joystick to be positioned close to the armrest
while remaining accessible to the user.

### Battery Monitoring

The battery indicator initially required careful configuration
before it could correctly detect the voltage of the 12 V battery.

I first soldered wires to the positive and negative terminals of the
battery indicator. I then researched the appropriate terminal/row
configuration required for the indicator to operate within the
voltage range of the battery.

With assistance from a lab assistant, I performed micro-soldering
to establish the required connections while avoiding short
circuits. After the connections were completed and tested, the
battery indicator successfully began displaying the battery voltage.

## Development Journal

The complete project journal documents the development process,
including design decisions, hardware integration, testing,
challenges encountered, and prototype development.

📘 **[View Complete Project Journal](https://docs.google.com/document/d/1CIjM_xLYNCckEMdnfBFI1WbFrF81M3wR/edit?usp=drive_link&ouid=100130635653822734064&rtpof=true&sd=true)**

## Future Improvements

The current prototype provides a foundation for further development.
Potential improvements include:

- Replacing the cardboard structural components with stronger and
  lightweight materials such as acrylic, aluminium, or engineered
  polymer components.
- Developing a more rigid and ergonomically designed joystick mount.
- Adding wheel encoders to enable closed-loop motor control and
  more precise movement.
- Expanding obstacle detection to provide more comprehensive
  coverage around the wheelchair.
- Integrating additional sensors or computer vision for improved
  environmental awareness.
- Developing autonomous or semi-autonomous navigation capabilities.
- Adding a more advanced battery management and monitoring system.
- Improving the mechanical chassis and conducting systematic load
  and durability testing.
- Developing a dedicated mobile application for wireless control
  and monitoring.
- Improving the emergency safety system with additional fail-safe
  mechanisms.

## Project Website

🌐 **[Visit the Smart Wheelchair Project Website](https://milo-the-wheelchair.ai.studio)**

The project website will provide a visual overview of the
wheelchair, its development process, hardware, software,
engineering challenges, testing, and future improvements.
