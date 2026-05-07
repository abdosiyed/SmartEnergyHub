# SmartEnergyHub

> A complete IoT solution for intelligent household energy management using ESP32 microcontroller with a web-based dashboard and REST API.

[![Built with PlatformIO](https://img.shields.io/badge/Built%20with-PlatformIO-orange)](https://platformio.org/)
[![Arduino Mega](https://img.shields.io/badge/Platform-Arduino%20Mega-blue)](https://www.arduino.cc/en/products/boards/arduino-mega-2560)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 📋 Table of Contents

- [Features](#features)
- [Architecture](#architecture)
- [Hardware Requirements](#hardware-requirements)
- [Pin Configuration](#pin-configuration)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [API Reference](#api-reference)
- [Contributing](#contributing)

## ✨ Features

- **Real-time Power Monitoring**: Track power consumption across 4 independent rooms simultaneously
- **Web Dashboard**: Interactive web-based interface for complete system control and visualization
- **Overload Protection**: Automatic detection and alerting for room and home-level power overloads
- **Manual Control**: Physical switches for room-by-room power management
- **Status Display**: 20x4 LCD screen showing real-time room status and power metrics
- **REST API**: Full-featured API for integration with third-party systems
- **Non-blocking Operation**: All timing uses millisecond-based checks for responsive behavior
- **5-Layer Architecture**: Clean, maintainable code with strict layered separation of concerns

## 🏗️ Architecture

SmartEnergyHub implements a strict **5-layer architecture** with unidirectional dependencies:

```
┌─────────────────────────────────────┐
│  main.cpp (Entry Point)             │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│  APP Layer - Orchestration          │
│  (Coordinates all subsystems)       │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│  Service Layer - Business Logic     │
│  (Monitor, Room, Display, UART)     │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│  HAL Layer - Hardware Abstraction   │
│  (LED, LCD, Switch, Sensor drivers) │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│  MCAL Layer - Microcontroller       │
│  (GPIO, ADC, UART, Timer)           │
└─────────────────────────────────────┘
```

### Layer Responsibilities

- **MCAL (Microcontroller Abstraction Layer)**: Low-level hardware register access (GPIO, ADC, UART, timers)
- **HAL (Hardware Abstraction Layer)**: Device driver implementations (LED control, LCD communication, switch debouncing, sensor reading)
- **Service Layer**: Business logic and system state management (room monitoring, power calculation, display updates)
- **APP Layer**: Orchestration and coordination of all subsystems
- **Main**: Entry point only; contains setup() and loop() calling app.run()

## 🛠️ Hardware Requirements

### Microcontroller
- **Arduino Mega 2560** (ATmega2560, 16MHz, 8KB RAM, 256KB Flash)

### Sensors & Components
- **4x Analog Power Sensors**: Linear ADC mapping to 0-2000W per room
- **4x Manual Switches**: Room control (with 50ms debounce)
- **4x Status LEDs**: Room status indication with overload blinking
- **1x 20x4 I2C LCD Display**: Real-time system status display (I2C address: 0x27)
- **1x UART Serial Connection**: Communication with Flask server (115200 baud)

### Libraries
- **ArduinoJson 7.0.4**: JSON parsing and building
- **LiquidCrystal_I2C 1.1.2**: LCD control via I2C

## 📍 Pin Configuration

### ADC Sensors (Power Measurement)
| Room | Analog Pin | ADC Channel |
|------|----------|----------|
| Living Room (R1) | A0 | 0-2000W |
| Kitchen (R2) | A1 | 0-2000W |
| Bedroom 1 (R3) | A2 | 0-2000W |
| Bedroom 2 (R4) | A3 | 0-2000W |

### Manual Switches (Input, INPUT_PULLUP)
| Room | GPIO Pin | Action |
|------|----------|--------|
| Living Room (R1) | 2 | Toggle R1 ON/OFF |
| Kitchen (R2) | 3 | Toggle R2 ON/OFF |
| Bedroom 1 (R3) | 4 | Toggle R3 ON/OFF |
| Bedroom 2 (R4) | 5 | Toggle R4 ON/OFF |

### Status LEDs (Output, HIGH=ON)
| Room | GPIO Pin | Behavior |
|------|----------|----------|
| Living Room (R1) | 6 | ON/OFF or 300ms blink (overload) |
| Kitchen (R2) | 7 | ON/OFF or 300ms blink (overload) |
| Bedroom 1 (R3) | 8 | ON/OFF or 300ms blink (overload) |
| Bedroom 2 (R4) | 9 | ON/OFF or 300ms blink (overload) |

### I2C LCD Display
| Signal | GPIO Pin |
|--------|----------|
| SDA (Data) | 20 |
| SCL (Clock) | 21 |
| Address | 0x27 |
| Resolution | 20x4 |

### UART Serial Communication
| Parameter | Value |
|-----------|-------|
| Speed | 115200 baud |
| TX Pin | GPIO 1 (default UART0) |
| RX Pin | GPIO 0 (default UART0) |
| Note | Arduino Mega has 4 UARTs; default Serial uses TX0/RX0 |

## 📦 Installation

### Prerequisites
- [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html) or [PlatformIO IDE](https://platformio.org/install/ide)
- Git
- Python 3.8+ (for Flask server)

### Firmware Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/abdosiyed/SmartEnergyHub.git
   cd SmartEnergyHub
   ```

2. **Build the firmware**
   ```bash
   platformio run
   ```

3. **Upload to ESP32**
   ```bash
   platformio run --target upload
   ```

4. **Monitor Serial Output**
   ```bash
   platformio device monitor --baud 115200
   ```

### Server Setup

1. **Install Python dependencies**
   ```bash
   cd server
   pip install -r requirements.txt
   ```

2. **Configure UART Port** (edit `server/server.py`)
   ```python
   UART_PORT = 'COM3'  # Change to your ESP32 port
   ```

3. **Run the Flask server**
   ```bash
   python server.py
   ```

4. **Access the dashboard**
   - Open browser: `http://localhost:5000`
   - View real-time power data and control rooms

## 🚀 Usage

### Web Dashboard
- **View Real-time Data**: Power consumption per room updates every 2 seconds
- **Toggle Rooms**: Click ON/OFF buttons to control room power
- **Set Limits**: Adjust individual room max power thresholds
- **Home Budget**: Set total home power budget and monitor remaining capacity

### Physical Controls
- **Manual Switches**: Press switch to toggle room ON/OFF (50ms debounce)
- **Status LEDs**: 
  - Solid: Room is ON
  - Off: Room is OFF
  - Blinking: Overload detected (300ms interval)
- **LCD Display**: Shows active room status and total system power

### API Endpoints

#### Get System Status
```bash
GET /data
```
Response:
```json
{
  "R1": {"name": "Living Room", "power": 1500, "state": "ON"},
  "R2": {"name": "Kitchen", "power": 800, "state": "OFF"},
  "R3": {"name": "Bedroom 1", "power": 200, "state": "ON"},
  "R4": {"name": "Bedroom 2", "power": 0, "state": "OFF"},
  "total": 2500
}
```

#### Toggle Room
```bash
POST /toggle?room=R1
```

#### Set Room Max Power
```bash
POST /set_mp?room=R1&value=1500
```

#### Set Home Budget
```bash
POST /set_hp?value=5000
```

## 📁 Project Structure

```
SmartEnergyHub/
├── README.md                          # Project documentation
├── platformio.ini                     # PlatformIO build configuration
├── .gitignore                         # Git ignore rules
│
├── include/
│   └── config.h                       # Global constants & pin definitions
│
├── src/
│   ├── main.cpp                       # Entry point
│   │
│   ├── mcal/                          # Microcontroller Abstraction Layer
│   │   ├── adc.h/.cpp                 # Analog-to-digital converter
│   │   ├── gpio.h/.cpp                # Digital I/O operations
│   │   ├── uart.h/.cpp                # Serial communication
│   │   └── timer.h/.cpp               # Timing utilities
│   │
│   ├── hal/                           # Hardware Abstraction Layer
│   │   ├── lcd.h/.cpp                 # 20x4 I2C LCD display driver
│   │   ├── led.h/.cpp                 # LED control with blinking
│   │   ├── switch.h/.cpp              # Switch input with debouncing
│   │   └── sensor.h/.cpp              # Power sensor reading
│   │
│   ├── service/                       # Service Layer - Business Logic
│   │   ├── room.h/.cpp                # Room class with state & power
│   │   ├── monitor.h/.cpp             # System monitor & overload detection
│   │   ├── uart_comm.h/.cpp           # UART communication service
│   │   └── display.h/.cpp             # Display update logic
│   │
│   ├── app/                           # APP Layer - Orchestration
│   │   └── app.h/.cpp                 # Main application coordinator
│   │
│   └── utilities/                     # Helper utilities
│       ├── json_builder.h/.cpp        # JSON string construction
│       └── json_parser.h/.cpp         # JSON command parsing
│
└── server/                            # Flask web server
    ├── server.py                      # Flask app with UART reader
    ├── requirements.txt               # Python dependencies
    └── templates/
        └── index.html                 # Web dashboard UI
```

## 🔌 Communication Protocol

### UART JSON Format (115200 baud)

**Room Status (ESP32 → Server, every 2 seconds)**
```json
{"R1":{"name":"Living Room","power":1500,"state":"ON"},"R2":{"name":"Kitchen","power":800,"state":"OFF"},"R3":{"name":"Bedroom 1","power":200,"state":"ON"},"R4":{"name":"Bedroom 2","power":0,"state":"OFF"},"total":2500}
```

**Commands (Server → ESP32)**
```json
{"cmd":"TOGGLE","room":"R1"}
{"cmd":"SET_MP","room":"R2","value":1000}
{"cmd":"SET_HP","value":5000}
```

## 📊 System States

| State | Description | LED Behavior |
|-------|-------------|--------------|
| MONITORING | Normal operation | Per-room ON/OFF |
| ROOM_OVERLOAD_ALERT | Individual room exceeds limit | Overloaded room blinks |
| HOME_OVERLOAD_ALERT | Total power exceeds home budget | All room LEDs blink |

## 🛡️ Power Calculation

```
Power (Watts) = (ADC_Reading × 2000) / 4095
```
- ADC range: 0-4095
- Sensor range: 0-2000W (linear)
- Update interval: Non-blocking per loop iteration

## 📝 Build Information

- **Platform**: ATmega AVR v5.4.0
- **Framework**: Arduino
- **Build Mode**: Release (optimized)
- **Flash Usage**: ~20 KB (≈8%)
- **RAM Usage**: ~4 KB (≈50%)
- **Compilation Time**: ~30 seconds (first build)
- **MCU**: ATmega2560, 16 MHz, 8 KB SRAM, 256 KB Flash

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 📧 Contact

**Author**: Abdelrahman Sayed  
**Email**: abdo.siyed.official@gmail.com  
**GitHub**: [@abdosiyed](https://github.com/abdosiyed)

---

**Built with ❤️ for intelligent energy management**
