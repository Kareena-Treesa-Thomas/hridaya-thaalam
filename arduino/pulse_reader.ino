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
const int pulsePin = A0;

// ---------- SETTINGS ----------
const int MIN_BPM = 45;
const int MAX_BPM = 140;

const int MIN_INTERVAL = 430;   // ~140 BPM maximum
const int MAX_INTERVAL = 1330;  // ~45 BPM minimum

// How much the signal must rise above baseline
int peakHeight = 40;

// ---------- VARIABLES ----------
float baseline = 0;
float signal = 0;

float peak = 0;

bool abovePeak = false;

unsigned long lastBeatTime = 0;

// Smoothed BPM
float displayedBPM = 0;

void setup() {

  Serial.begin(9600);

  // Get initial baseline
  long total = 0;

  for (int i = 0; i < 100; i++) {
    total += analogRead(pulsePin);
    delay(5);
  }

  baseline = total / 100.0;

  Serial.println("Place finger on sensor...");
}

void loop() {

  signal = analogRead(pulsePin);

  // Slowly follow the signal baseline
  baseline = baseline * 0.995 + signal * 0.005;

  // Difference from baseline
  float difference = signal - baseline;

  unsigned long now = millis();

  // ------------------------------------------------
  // PEAK DETECTION
  // ------------------------------------------------

  if (difference > peakHeight && !abovePeak) {

    abovePeak = true;

    // Time since previous beat
    if (lastBeatTime > 0) {

      unsigned long interval = now - lastBeatTime;

      // Accept only realistic heartbeat intervals
      if (interval >= MIN_INTERVAL &&
          interval <= MAX_INTERVAL) {

        float newBPM = 60000.0 / interval;

        // First valid BPM
        if (displayedBPM == 0) {

          displayedBPM = newBPM;

        } else {

          // Gentle smoothing
          displayedBPM =
            displayedBPM * 0.70 +
            newBPM * 0.30;
        }

        Serial.print("❤️ BEAT   BPM: ");
        Serial.println(displayedBPM, 1);

        // ------------------------------------------
        // MUSIC TRIGGER
        // ------------------------------------------

        // Play your note HERE
        //
        // Example:
        // tone(8, 440, 100);

      }

    }

    lastBeatTime = now;
  }

  // Signal must come down before another beat
  if (difference < peakHeight / 2) {
    abovePeak = false;
  }

  delay(2);
}