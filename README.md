# hridaya-thaalam
Hridaya Thaalam is a hardware-to-web pipeline that reads a heartbeat via an Arduino pulse sensor, learns your personal baseline, classifies your state as Relaxed/Normal/Elevated, and turns it into live music and a real-time web dashboard with a BPM graph.

## Basic Details
### Team Name: Hridaya Thaalam

### Team Members
- Team Lead: [Your Name] - [College Name]
- Member 2: [Name] - [College Name]
- Member 3: [Name] - [College Name]

### Project Description
Hridaya Thaalam is a heartbeat-driven music experience that converts pulse data into live musical notes and visual rhythm. It turns the body’s natural pulse into a personal, reactive soundtrack without needing any heavy hardware output.

### The Problem (that doesn't exist)
People usually stare at heart-rate monitors like they are reading a tax document. We wanted to make heartbeat data feel alive, expressive, and musical instead of dull and clinical.

### The Solution (that nobody asked for)
We connected a pulse sensor to an Arduino, read live BPM in the browser, and mapped heartbeat changes to a melodic note system. The result is a real-time pulse-to-music dashboard where the heart becomes the conductor.

## Technical Details
### Technologies/Components Used
For Software:
- HTML, CSS, JavaScript
- Web Audio API
- WebSerial API
- Arduino serial communication
- Chrome/Edge browser support
- Local HTTP server for testing

For Hardware:
- Pulse sensor module
- Arduino Uno / compatible board
- USB cable
- Jumper wires
- Breadboard (optional)
- Power source for Arduino

### Implementation
For Software:
# Installation
```bash
cd hridaya-thaalam
cd web
python -m http.server 8000
```

# Run
1. Upload the Arduino sketch from `arduino/pulse_reader.ino` using the Arduino IDE.
2. Open the browser on `http://localhost:8000` in Chrome or Edge.
3. Click `Connect sensor` to link the Arduino over serial.
4. If needed, use `Run simulated data` for testing without hardware.

### Project Documentation
For Software:

# Screenshots (Add at least 3)
![Screenshot1](Add screenshot 1 here with proper name)
*Live dashboard showing BPM, waveform, and heartbeat-driven music UI.*

![Screenshot2](Add screenshot 2 here with proper name)
*Pulse graph and musical note response in real time.*

![Screenshot3](Add screenshot 3 here with proper name)
*State change and music generation based on heartbeat variation.*

# Diagrams
![Workflow](Add your workflow/architecture diagram here)
*The pulse sensor reads data, Arduino sends BPM over serial, and the browser maps it to music and visualization.*

For Hardware:

# Schematic & Circuit
![Circuit](Add your circuit diagram here)
*Pulse sensor connected to Arduino analog input and powered through the board.*

![Schematic](Add your schematic diagram here)
*Basic analog heart-rate sensing circuit using the pulse sensor module.*

# Build Photos
![Components](Add photo of your components here)
*List out all components shown: pulse sensor, Arduino board, USB cable, jumper wires.*

![Build](Add photos of build process here)
*Explain the build steps: sensor wiring, board upload, and browser setup.*

![Final](Add photo of final product here)
*The final demo setup showing the sensor connected and the rhythm dashboard running.*

### Project Demo
# Video
[Add your demo video link here]
*Explain what the video demonstrates: live pulse to melody conversion and dashboard response.*

# Additional Demos
[Add any extra demo materials/links]

## Team Contributions
- [Name 1]: Designed the heartbeat-to-music logic and UI dashboard.
- [Name 2]: Worked on Arduino pulse sensing and serial communication.
- [Name 3]: Integrated the live visuals, note mapping, and testing.

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)
