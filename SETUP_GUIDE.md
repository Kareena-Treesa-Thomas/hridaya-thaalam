# Hridaya Thaalam — Nadapaatu Naadi
## Complete Setup Guide — Hardware, Software & Music Integration

This is the single reference document for building and running the project.
Follow it top to bottom. Every section tells you exactly what file it
touches and how to test that step before moving to the next one.

---

## 0. What you're building — the full picture

```
Pulse sensor (finger)
      │  analog signal
      ▼
  Arduino Uno (arduino/pulse_reader.ino)
      │  USB cable, prints "BPM:73\n" per detected heartbeat
      ▼
  Browser — Chrome or Edge (web/index.html)
      │  navigator.serial reads the line directly, no backend server
      ▼
  ┌─────────────────────────────────────────┐
  │  1. Calibration — first 10 beats set     │
  │     your personal resting baseline       │
  │  2. State engine — RELAXED/NORMAL/       │
  │     ELEVATED, based on distance from     │
  │     baseline, debounced against noise    │
  │  3. Note engine — 7-note Sa–Ni scale,    │
  │     picked by that same distance         │
  │  4. Music engine — Web Audio plays the   │
  │     note; volume/decay scale with state  │
  │  5. UI — every number on screen reflects │
  │     the above, nothing is fabricated     │
  └─────────────────────────────────────────┘
```

There is no cloud service, no API key, and no account required anywhere
in this pipeline. Everything runs locally on the demo laptop.

---

## 1. Hardware — wiring and upload

**Parts needed:** Arduino Uno (or compatible), a pulse sensor module,
3 jumper wires, USB cable (must be a data cable, not charge-only).

**Wiring:**

| Pulse sensor pin | Arduino pin |
|---|---|
| VCC | 5V |
| GND | GND |
| Signal | A0 |

**Upload the sketch:**

1. Open `arduino/pulse_reader.ino` in the Arduino IDE.
2. Select your board and COM port under Tools.
3. Click Upload.

**Tune the threshold — do this before anything else, it's the #1 cause of "nothing works":**

1. Open Tools → Serial Plotter.
2. Place a finger on the sensor and hold still.
3. Watch the raw signal — note the resting (low) value and the peak
   (high) value during a beat.
4. In the sketch, set `THRESHOLD` to roughly halfway between them.
5. Re-upload, and confirm the Serial Monitor prints lines like
   `BPM:74` in time with the actual pulse.

**Test with the real presenter, not just your own finger.** Skin
tone, finger pressure, and circulation all shift the ideal threshold.
Retune it with whoever is actually demoing.

---

## 2. Software — serving and connecting the website

WebSerial (the API that reads the Arduino) refuses to run on a plain
`file://` page — it needs to be served.

1. Open a terminal in the `web/` folder.
2. Run:
   ```
   python3 -m http.server 8000
   ```
3. Open `http://localhost:8000` in **Chrome or Edge** (Safari and
   Firefox don't support WebSerial — check this on your actual demo
   laptop ahead of time, not on stage).
4. Click **Connect sensor**. A device picker appears — select the
   Arduino's serial port.
   - If nothing appears or it fails: close the Arduino IDE's Serial
     Monitor/Plotter first. Only one program can hold the port at a
     time — this is the most common connection failure.
5. Put a finger on the sensor. The page collects 10 beats to compute
   your baseline, then goes fully live.

**No hardware yet, or hardware acting up?** Click **Run simulated
data** instead. It drives the exact same pipeline — calibration,
state engine, music, and UI — with a synthetic signal. Use this to
build and rehearse before the sensor is ready, and as your live
fallback if the sensor misbehaves during the actual demo.

---

## 3. How the state and note engine actually works

Once baseline is set, every incoming BPM is converted to `delta = bpm - baseline`.

**Note selection (Sa–Ni, 7 notes):**

| delta range | Note |
|---|---|
| ≤ -8 | Sa |
| -8 to -5 | Re |
| -5 to -2 | Ga |
| -2 to 2 | Ma |
| 2 to 5 | Pa |
| 5 to 8 | Dha |
| ≥ 8 | Ni |

**State selection:**

| delta | State |
|---|---|
| ≤ -5 | RELAXED |
| -5 to 5 | NORMAL |
| ≥ 5 | ELEVATED |

**Debouncing:** a state only changes after 3 consecutive readings agree
on the new state. This stops a single noisy beat from flickering the
UI during a live demo where the sensor will be somewhat unstable.

**Music response (tempo/volume — genuinely computed, not decorative):**

- `speed%` and `intensity%` scale with how far delta is from zero
  (clamped to ±15 bpm). Further from baseline = faster, louder,
  snappier notes. Closer to baseline = slower, softer, longer notes.
- `pitch%` reflects where the current note sits on the Sa–Ni scale.
- These three numbers directly set the oscillator's volume and decay
  time in the audio engine — they're not just UI decoration.

All of this logic lives in `web/index.html`, inside the `<script>`
block — search for `processBPM`, `noteForDelta`, `stateForDelta`, and
`updateMusicResponse` if you need to retune the thresholds.

---

## 4. Music — how sound is generated

No sample files, no external library. Each note is synthesized live
using the Web Audio API: a triangle oscillator through a lowpass
filter, with a volume envelope (quick attack, exponential decay) that
gives it a plucked-string character.

- To change which frequencies map to which note, edit the `NOTE_FREQ`
  object in the script.
- To make notes sound different (e.g. more sustained, more percussive),
  adjust the `decaySeconds` calculation or the oscillator `type`
  (`'triangle'`, `'sine'`, `'sawtooth'`, `'square'`).
- No setup required — this works the instant the page loads, in any
  browser, with zero configuration.

---

---

## 5. UI — what's real vs. what's cosmetic

Everything numeric on the page is driven by live data. For full
transparency, here's what's genuinely computed versus what's static
branding copy:

**Live/real:** BPM number, both EKG graphs, state gauge needle and
label, melody speed/pitch/intensity bars, current note, note history,
device status (input source and last-beat freshness), calibration progress.

**Static/decorative (by design, not hidden):** the hero tagline copy,
the "Your heartbeat is the conductor" card, and the sidebar items
beyond Dashboard (History, Settings, About Project are inert — clicking
them does nothing). If a judge asks, say so plainly; it's a known,
intentional scope cut, not a bug.

---

## 6. Pre-hackathon checklist

- [ ] Sensor wired, sketch uploaded, threshold tuned with the **actual
      presenter's finger**
- [ ] `python3 -m http.server` + WebSerial connection tested on the
      **actual demo laptop**, in Chrome or Edge
- [ ] Full pipeline run once end-to-end with the real sensor: calibrate
      → state change → note plays
- [ ] "Run simulated data" tested standalone, with zero hardware
      plugged in — this is your live fallback
- [ ] Spare USB data cable and spare sensor packed
- [ ] Project copied to a USB stick or offline repo — don't rely on
      venue wifi for your only copy
- [ ] Everything charged the night before
- [ ] Fallback transition rehearsed: know exactly which button you
      click if the sensor drops out live

---

## 7. Troubleshooting quick reference

| Symptom | Likely cause | Fix |
|---|---|---|
| Serial Monitor shows nothing | Wrong `THRESHOLD`, or sensor not touching skin firmly | Re-tune via Serial Plotter |
| "Connect sensor" popup shows no device | Arduino IDE still has the port open | Close Serial Monitor/Plotter in the IDE |
| Page loads but WebSerial button does nothing | Wrong browser, or page opened as `file://` | Use Chrome/Edge, serve via `http.server` |
| BPM jumps wildly / state flickers | Sensor noise, poor contact | Debounce already handles minor cases; check finger placement |
| No sound at all | Browser blocked audio autoplay | Click anywhere on the page once before expecting audio (browser autoplay policy) |

---

## 8. File map

```
hridaya-thaalam/
├── README.md                    ← integration overview (shorter version of this doc)
├── SETUP_GUIDE.md                ← this file
├── arduino/
│   └── pulse_reader.ino          ← uploads to the Arduino, prints BPM over serial
└── web/
    └── index.html                 ← the entire app: UI, calibration, state engine,
                                      music synthesis, and WebSerial
```
