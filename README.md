---

title: Hridaya Thaalam
emoji: 💓
colorFrom: red
colorTo: blue
sdk: static
tags:
- arduino
- pulse-sensor
- heartbeat
- web-audio
- web-serial
- music
- real-time
- hardware
pinned: false
license: mit
short_description: Real-time heartbeat-to-music interactive hardware-to-web experience.

---

# 💓 Hridaya Thaalam — Heartbeat to Music

[![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=flat-square)](https://www.arduino.cc/)
[![JavaScript](https://img.shields.io/badge/JavaScript-ES6-F7DF1E?style=flat-square)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
[![Web Audio API](https://img.shields.io/badge/Web_Audio-API-4285F4?style=flat-square)](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API)
[![Web Serial API](https://img.shields.io/badge/Web_Serial-API-34A853?style=flat-square)](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API)
[![License: MIT](https://img.shields.io/badge/License-MIT-f59e0b?style=flat-square)](LICENSE)

---

**Hridaya Thaalam** is a hardware-to-web pipeline that reads a heartbeat through an
**Arduino pulse sensor**, learns the user's personal baseline, classifies their state
as **Relaxed / Normal / Elevated**, and transforms heartbeat changes into **live music**
and a real-time web dashboard with BPM visualization.

Instead of treating heart-rate data as a simple number, Hridaya Thaalam turns the
body's natural rhythm into an interactive musical experience — making the heart the
conductor.

---

## 🗺 Project Overview

| Property            | Value                            |
| ------------------- | -------------------------------- |
| **Domain**          | Interactive Hardware + Web       |
| **Input**           | Pulse Sensor                     |
| **Microcontroller** | Arduino Uno                      |
| **Communication**   | USB Serial / Web Serial API      |
| **Processing**      | JavaScript                       |
| **Audio Engine**    | Web Audio API                    |
| **Output**          | BPM, graph, state, musical notes |
| **States**          | Relaxed / Normal / Elevated      |
| **Audio Output**    | Laptop Speaker                   |
| **Testing**         | Real Sensor + Simulated Data     |
| **Browser**         | Chrome / Microsoft Edge          |

---

## ⚡ Quick Start

### Hardware Setup

Connect the pulse sensor to the Arduino Uno:

```text
Pulse Sensor          Arduino Uno
─────────────         ───────────
VCC       ──────────► 5V
GND       ──────────► GND
SIGNAL    ──────────► A0
```

Upload the Arduino sketch:

```text
arduino/pulse_reader.ino
```

using the **Arduino IDE**.

---

### Web Application

Clone the repository and start a local HTTP server:

```bash
git clone https://github.com/Kareena-Treesa-Thomas/hridaya-thaalam.git
cd hridaya-thaalam
cd web
python -m http.server 8000
```

Open:

```text
http://localhost:8000
```

in **Google Chrome** or **Microsoft Edge**.

Then:

1. Upload the Arduino sketch.
2. Connect the Arduino through USB.
3. Open the web application.
4. Click **Connect Sensor**.
5. Select the Arduino serial port.
6. Place your finger on the pulse sensor.
7. Wait for the BPM to stabilize.
8. Watch the heartbeat influence the dashboard and music.

For testing without the physical sensor, use:

```text
Run Simulated Data
```

---

## 🎵 Project Description

Hridaya Thaalam is a heartbeat-driven music experience that converts pulse data into
live musical notes and visual rhythm.

The system captures the user's heartbeat through a pulse sensor connected to an
Arduino. The heartbeat information is transmitted to a browser, where it is processed
and visualized.

The system then maps heartbeat changes to musical notes, creating a personal,
reactive soundtrack without requiring any heavy external audio hardware.

---

## 🤔 The Problem (that doesn't exist)

People usually stare at heart-rate monitors like they are reading a tax document.

A BPM value such as:

```text
72 BPM
```

contains useful information, but it is not particularly expressive or engaging.

We wanted to make heartbeat data feel **alive, visual, expressive, and musical**
instead of dull and clinical.

---

## 💡 The Solution (that nobody asked for)

We connected a pulse sensor to an Arduino, read live BPM in the browser, learned the
user's personal baseline, and mapped heartbeat changes to a melodic note system.

The result is a real-time pulse-to-music dashboard where:

```text
❤️ Heartbeat
     │
     ▼
📈 BPM
     │
     ▼
🧠 Personal Baseline
     │
     ▼
😌 State Classification
     │
     ▼
🎵 Musical Notes
     │
     ▼
🔊 Laptop Speaker
```

The heart becomes the conductor.

---

## 🔌 System Architecture

```text
┌─────────────────────┐
│    Pulse Sensor     │
│  Heartbeat Signal   │
└──────────┬──────────┘
           │
           │ Analog Signal
           ▼
┌─────────────────────┐
│     Arduino Uno     │
│   Pulse Detection   │
│     BPM Reading     │
└──────────┬──────────┘
           │
           │ USB Serial
           ▼
┌─────────────────────┐
│   Web Serial API    │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────────────┐
│       JavaScript App        │
│                             │
│  ┌───────────────────────┐  │
│  │ BPM Processing        │  │
│  ├───────────────────────┤  │
│  │ Baseline Learning     │  │
│  ├───────────────────────┤  │
│  │ State Classification   │  │
│  ├───────────────────────┤  │
│  │ Note Mapping           │  │
│  └───────────────────────┘  │
└──────────┬───────────┬──────┘
           │           │
           ▼           ▼
    ┌────────────┐ ┌──────────────┐
    │ Dashboard  │ │ Web Audio API│
    │ BPM + Graph│ │ Music Output │
    └────────────┘ └───────┬──────┘
                           │
                           ▼
                    🔊 Laptop Speaker
```

---

## 🧠 How It Works

### 1. Pulse Detection

The pulse sensor detects changes in blood flow caused by the heartbeat and produces
an analog signal.

The Arduino reads this signal through its analog input.

```text
Pulse Sensor
     │
     ▼
Analog Signal
     │
     ▼
Arduino Analog Input A0
```

### 2. BPM Calculation

The Arduino identifies heartbeat events and calculates the approximate beats per
minute.

```text
BPM = Beats Per Minute
```

The BPM data is then sent to the browser through USB serial communication.

### 3. Personal Baseline

Instead of applying identical thresholds to every person, Hridaya Thaalam first
observes the user's heartbeat and establishes a personal baseline.

This makes the interactive experience responsive to changes relative to the user's
own heartbeat.

### 4. State Classification

The current heartbeat is compared against the learned baseline.

| State        | Description                                         |
| ------------ | --------------------------------------------------- |
| **Relaxed**  | Heartbeat is relatively below the personal baseline |
| **Normal**   | Heartbeat is close to the personal baseline         |
| **Elevated** | Heartbeat is relatively above the personal baseline |

> **Note:** These states are designed for an interactive project experience and are
> not intended to provide medical diagnosis or clinical assessment.

---

## 🎶 Heartbeat-to-Music Mapping

The heartbeat is not simply displayed as a number.

Changes in heartbeat are translated into musical parameters.

```text
Heartbeat
    │
    ▼
BPM + Variation
    │
    ▼
State Detection
    │
    ▼
Musical Note Selection
    │
    ▼
Web Audio API
    │
    ▼
Laptop Speaker
```

This creates a direct relationship between the user's physical pulse and the
generated musical output.

---

## 📊 Real-Time Dashboard

The web dashboard provides a live view of the heartbeat and generated response.

| Component           | Description                                |
| ------------------- | ------------------------------------------ |
| **BPM Display**     | Shows the current estimated heartbeat rate |
| **Heartbeat Graph** | Displays BPM changes over time             |
| **State Indicator** | Shows Relaxed, Normal, or Elevated         |
| **Music Response**  | Displays the current musical response      |
| **Connect Sensor**  | Connects the browser to the Arduino        |
| **Simulation Mode** | Tests the system without physical hardware |

---

## 🧪 Simulation Mode

The project supports simulated heartbeat data so that the web application can be
tested without connecting the Arduino.

```text
Run Simulated Data
        │
        ▼
   Simulated BPM
        │
        ├──────────► BPM Display
        │
        ├──────────► Heartbeat Graph
        │
        ├──────────► State Classification
        │
        └──────────► Music Generation
```

This allows the software components to be tested independently from the hardware.

---

# 🛠 Technical Details

## Technologies / Components Used

### For Software

* HTML
* CSS
* JavaScript
* Web Audio API
* Web Serial API
* Arduino Serial Communication
* Chrome / Microsoft Edge
* Local HTTP Server

### For Hardware

* Pulse Sensor Module
* Arduino Uno / compatible board
* USB Cable
* Jumper Wires
* Breadboard (optional)
* Power source for Arduino

---

## 💻 Implementation

### Software

#### Installation

```bash
cd hridaya-thaalam
cd web
python -m http.server 8000
```

#### Run

1. Upload the Arduino sketch from `arduino/pulse_reader.ino` using the Arduino IDE.
2. Open `http://localhost:8000` in Chrome or Edge.
3. Click **Connect Sensor** to link the Arduino over serial.
4. Select the correct Arduino serial port.
5. Place your finger on the pulse sensor.
6. Wait for the heartbeat signal and baseline to stabilize.
7. Observe the BPM, graph, state and music response.
8. If hardware is unavailable, use **Run Simulated Data**.

---

## 🌐 Browser Requirements

Hridaya Thaalam uses the **Web Serial API** for communication between the browser and
Arduino.

Recommended browsers:

* Google Chrome
* Microsoft Edge

The project should be served through a local HTTP server instead of opening
`index.html` directly using a `file://` URL.

---

# 📁 Project Structure

```text
hridaya-thaalam/
├── arduino/
│   └── pulse_reader.ino
│       # Arduino pulse sensor reader
│       # Reads heartbeat signal and sends
│       # BPM data through serial communication
│
├── web/
│   └── index.html
│       # Main dashboard interface
│       # BPM processing, graph, state, audio
│
├── README.md
├── SETUP_GUIDE.md
└── LICENSE
```

---

# 📸 Project Documentation

## For Software

### Screenshots

> Add your screenshots here when preparing the final demo.

![Live Dashboard](screenshots/dashboard.png)

*Live dashboard showing BPM, waveform, and heartbeat-driven music UI.*

![BPM Graph](screenshots/bpm-graph.png)

*Pulse graph and musical note response in real time.*

![State and Music](screenshots/state-music.png)

*State change and music generation based on heartbeat variation.*

---

## 🔄 Workflow / Architecture Diagram

![Workflow](screenshots/workflow.png)

*The pulse sensor reads heartbeat data, Arduino processes and sends BPM over serial,
and the browser maps it to music and real-time visualization.*

---

# 🔧 For Hardware

## Schematic & Circuit

![Circuit](hardware/circuit.png)

*Pulse sensor connected to the Arduino analog input and powered through the board.*

![Schematic](hardware/schematic.png)

*Basic analog heart-rate sensing circuit using the pulse sensor module.*

---

## 📷 Build Photos

![Components](hardware/components.jpg)

*Components used in the project: pulse sensor, Arduino board, USB cable, jumper
wires and supporting hardware.*

![Build](hardware/build.jpg)

*Build process showing sensor wiring, Arduino setup and software integration.*

![Final](hardware/final-build.jpg)

*Final demo setup showing the pulse sensor connected to the Arduino and the rhythm
dashboard running on the laptop.*

---

# 🎥 Project Demo

## Video

[Add your demo video link here]

*The demonstration shows the complete pipeline from live pulse sensing to BPM
visualization, state classification and heartbeat-driven melody generation.*

---

## Additional Demos

[Add any extra demo materials or links]

Possible materials include:

* Additional demonstration videos
* Circuit demonstrations
* Simulation demonstrations
* Technical presentation
* Project poster
* GitHub repository
* Live web demo

---

# 👥 Team Contributions

* **[Name 1]**: Designed the heartbeat-to-music logic and UI dashboard.
* **[Name 2]**: Worked on Arduino pulse sensing and serial communication.
* **[Name 3]**: Integrated the live visuals, note mapping, and testing.

---

# 🚀 Future Improvements

* Improved heartbeat signal filtering
* More stable BPM detection
* Personalized musical scales
* Multiple musical instruments
* Heartbeat session history
* Wireless communication using Bluetooth or Wi-Fi
* Mobile-friendly dashboard
* More advanced state classification
* MIDI integration
* Improved visualization and audio effects

---

# ⚠️ Disclaimer

Hridaya Thaalam is an experimental interactive hardware project.

The BPM values and states displayed by the system are intended for demonstration and
creative interaction only. They should **not be used for medical diagnosis, treatment,
or clinical decision-making**.

---

Made with ❤️ at **TinkerHub Useless Projects**

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org/)

![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)

---

## 📄 License

MIT License
