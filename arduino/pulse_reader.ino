/*
  HRIDAYA THAALAM — pulse_reader.ino

  Reads a pulse sensor on A0, detects heartbeats using a simple
  threshold + refractory-period method, and prints one line per
  beat over Serial:

      BPM:73

  The website reads this line directly via the WebSerial API.
  No other Arduino-side logic is needed — all baseline/state/music
  logic lives in the browser.

  ------------------------------------------------------------
  TUNING (do this first, before anything else):
  1. Open Tools > Serial Plotter in the Arduino IDE.
  2. Watch the raw signal with your finger on the sensor.
  3. Note the resting value and the peak value during a beat.
  4. Set THRESHOLD roughly halfway between them.
  A bad threshold is the #1 reason this looks like it "doesn't work."
  ------------------------------------------------------------
*/

const int PULSE_PIN = A0;
const int THRESHOLD = 550;        // TUNE THIS — see notes above
const unsigned long REFRACTORY_MS = 300; // ignore beats closer than this (caps ~200 BPM)

unsigned long lastBeatTime = 0;
bool armed = true;       // true = watching for a rising edge
bool haveFirstBeat = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int signal = analogRead(PULSE_PIN);

  // Rising edge above threshold = candidate beat
  if (signal > THRESHOLD && armed) {
    unsigned long now = millis();
    unsigned long interval = now - lastBeatTime;

    if (!haveFirstBeat) {
      // First beat only sets the clock, no BPM yet (interval is meaningless)
      lastBeatTime = now;
      haveFirstBeat = true;
      armed = false;
    } else if (interval > REFRACTORY_MS) {
      int bpm = 60000 / interval;

      // Sanity filter — reject obviously bad readings (noise/movement)
      if (bpm >= 40 && bpm <= 200) {
        Serial.print("BPM:");
        Serial.println(bpm);
      }

      lastBeatTime = now;
      armed = false;
    }
  }

  // Signal dropped back down — re-arm for the next beat
  if (signal < THRESHOLD) {
    armed = true;
  }

  delay(10);
}
