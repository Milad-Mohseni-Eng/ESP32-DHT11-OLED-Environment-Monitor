# ESP32 DHT11 OLED Environment Monitor

An ESP32-based environmental monitoring system that measures ambient temperature and humidity using a DHT11 sensor and displays real-time information on an SSD1306 OLED display.

The system analyzes environmental conditions and classifies them into operational states using visual LED indicators. This project demonstrates sensor integration, OLED communication, GPIO control, and state-based embedded system design.

---

## Project Overview

This project continuously reads temperature and humidity values from a DHT11 sensor and displays the information on a 128×64 SSD1306 OLED display.

Based on predefined environmental thresholds, the system determines whether the environment is operating under:

- NORMAL conditions
- WARNING conditions
- CRITICAL conditions

Three LEDs provide instant visual feedback regarding the current system state.

This project is intended as an educational embedded systems project using ESP32 and Arduino Framework.

---

## Features

- Real-time temperature monitoring
- Real-time humidity monitoring
- SSD1306 OLED display output
- State-machine based system logic
- Green LED status indication
- Red LED status indication
- Blue LED status indication
- Sensor error detection
- ESP32 compatible
- Arduino IDE compatible

---

## Hardware Components

| Component | Quantity |
|------------|------------|
| ESP32 Development Board | 1 |
| DHT11 Temperature & Humidity Sensor | 1 |
| SSD1306 OLED Display (128×64) | 1 |
| Green LED | 1 |
| Red LED | 1 |
| Blue LED | 1 |
| 220Ω Resistors | 3 |
| Breadboard | 1 |
| Jumper Wires | Several |

---

## Pin Configuration

### DHT11 Sensor

| DHT11 Pin | ESP32 Pin |
|------------|------------|
| VCC | 3.3V |
| DATA | GPIO23 |
| GND | GND |

---

### SSD1306 OLED Display

| OLED Pin | ESP32 Pin |
|------------|------------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

### LEDs

| LED | ESP32 GPIO |
|---------|---------|
| Green LED | GPIO15 |
| Red LED | GPIO2 |
| Blue LED | GPIO4 |

---

## System States

### NORMAL

Conditions:

- Temperature ≤ 30°C
- Humidity ≤ 60%

Output:

- Green LED ON
- Red LED OFF
- Blue LED OFF

OLED displays:

```text
STATUS: NORMAL
```

---

### WARNING

Conditions:

- Temperature > 30°C
- OR
- Humidity > 60%

Output:

- Red LED ON
- Green LED OFF
- Blue LED OFF

OLED displays:

```text
STATUS: WARNING
```

---

### CRITICAL

Conditions:

- Temperature > 35°C
- OR
- Humidity > 75%

Output:

- Blue LED ON
- Green LED OFF
- Red LED OFF

OLED displays:

```text
STATUS: CRITICAL
```

---

### SENSOR ERROR

Triggered when:

```cpp
isnan(temperature)
```

or

```cpp
isnan(humidity)
```

returns true.

Output:

- Error indication
- OLED warning message
- System enters safe mode

OLED displays:

```text
STATUS: SENSOR ERROR
```

---

## How It Works

### Step 1

The ESP32 initializes:

- OLED Display
- DHT11 Sensor
- GPIO Outputs

---

### Step 2

The DHT11 sensor measures:

- Relative Humidity (%)
- Temperature (°C)

---

### Step 3

The ESP32 validates sensor readings.

If invalid data is detected:

```cpp
isnan()
```

the system enters SENSOR ERROR state.

---

### Step 4

The measured values are compared against predefined thresholds.

---

### Step 5

The system determines the current environmental state:

```cpp
NORMAL
WARNING
CRITICAL
```

---

### Step 6

The OLED updates the display with:

- Humidity
- Temperature
- System Status

---

### Step 7

LED indicators provide visual feedback regarding the current environmental condition.

---

## OLED Display Example

```text
SMART ENVIRONMENT

Humidity: 48%
Temp: 27C

STATUS: NORMAL
```

---

## Software Requirements

### Arduino IDE

Recommended version:

```text
Arduino IDE 2.x
```

---

### ESP32 Board Package

Install ESP32 boards from:

```text
Boards Manager
```

---

### Required Libraries

#### Adafruit SSD1306

Used for OLED display control.

#### Adafruit GFX

Graphics library required by SSD1306.

#### DHT Sensor Library

Used for communication with DHT11.

#### Adafruit Unified Sensor

Required dependency for DHT library.

---

## Educational Objectives

This project demonstrates:

### Sensor Interfacing

Reading data from a digital temperature and humidity sensor.

### OLED Communication

Displaying dynamic information using I²C communication.

### Embedded State Machines

Managing system behavior through defined operating states.

### Error Handling

Detecting invalid sensor readings using:

```cpp
isnan()
```

### GPIO Control

Controlling LEDs based on environmental conditions.

### Real-Time Monitoring

Continuous acquisition and display of sensor data.

---

## Project Structure

```text
ESP32-DHT11-OLED-Environment-Monitor
│
├── code
│   └── ESP32-DHT11-OLED-Environment-Monitor.ino
│
├── docs
│   ├── wiring.png
│   ├── circuit_diagram.png
│   └── oled_active.png
│
├── LICENSE
│
└── README.md
```

---

## Future Improvements

Potential future upgrades:

- Active buzzer alarm
- Temperature history tracking
- Humidity history tracking
- DHT22 sensor support
- Wi-Fi dashboard
- MQTT integration
- Mobile notifications
- SD card logging
- Web server monitoring
- Cloud connectivity

---

## Learning Outcomes

After completing this project, students will understand:

- ESP32 GPIO programming
- Sensor integration
- OLED display control
- I²C communication
- State-machine architecture
- Embedded error handling
- Environmental monitoring systems

---

## License

This project is licensed under the MIT License.

See the LICENSE file for details.

---

## Author

**Milad Mohseni**

Embedded Systems & IoT Developer

Technologies:

- ESP32
- Arduino Framework
- Embedded C/C++
- Sensors & Actuators
- OLED Displays
- IoT Prototyping

---

