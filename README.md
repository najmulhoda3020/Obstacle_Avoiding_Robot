🤖 Object Avoiding Robot - Arduino

An autonomous 4-wheel robot that detects obstacles using an ultrasonic sensor mounted on a servo, scans for a clear path, and navigates around them automatically.

---

## Components Used

| Component | Details |
|---|---|
| Microcontroller | Arduino Uno |
| Motor Driver | L293D (EN pins tied to 5V) |
| Distance Sensor | HC-SR04 Ultrasonic Sensor |
| Servo Motor | SG90 (for sensor scanning) |
| DC Motors | 4x TT Gear Motors |
| Power Supply | External battery pack |

---

## How It Works

1. Robot moves **forward** continuously while the path is clear
2. Ultrasonic sensor constantly measures distance to obstacles ahead
3. If an obstacle is detected within **30 cm**, the robot **stops**
4. The servo rotates the sensor **left** then **right** to scan both sides
5. Robot turns toward whichever side has **more open space**
6. If **both sides are blocked**, the robot **reverses** first, then turns
7. Robot resumes moving forward

---

## Pin Connections

### Ultrasonic Sensor (HC-SR04)
| Sensor Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | D9 |
| ECHO | D10 |

### Servo Motor
| Servo Pin | Arduino Pin |
|---|---|
| Signal | D6 |
| VCC | 5V |
| GND | GND |

### L293D Motor Driver
| Motor | IN1 | IN2 |
|---|---|---|
| Left Front | D2 | D3 |
| Right Front | D4 | D5 |
| Left Rear | D7 | D8 |
| Right Rear | D11 | D12 |

EN pins are tied directly to 5V on the module — no PWM speed control needed.

---

## Libraries Required

- [NewPing](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home) — Ultrasonic sensor
- Servo.h — Built into Arduino IDE

**Install NewPing:**
Arduino IDE → Tools → Manage Libraries → Search `NewPing` → Install

---

## Logic Summary

```
Moving Forward
     ↓
Distance < 30cm?
     ↓ YES
   STOP
     ↓
Scan Left → record distance
Scan Right → record distance
     ↓
Both blocked?  →  Reverse → then turn to better side
Only one blocked?  →  Turn to open side
     ↓
Resume Forward
```

---

## Built With

- Arduino IDE
- C++ (Arduino framework)

---
