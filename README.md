# digital-resonance-code

Max/MSP patches and Arduino firmware for a custom digital instrument built as part of a master's thesis at the Institute of Sonology, Royal Conservatoire, The Hague (2026).

The instrument consists of a latex membrane stretched above a 15-inch loudspeaker on a welded steel stand. Eight load cell sensors around the membrane read pressure distribution across its surface. Sensor data is sent over USB serial from an Arduino Mega to Max/MSP, where it is scaled, transformed, and mapped to synthesis parameters.

---

## Files

| File | Description |
|------|-------------|
| `Input_Scaling.maxpat` | Serial input, tare, scaling, and data transformation. Always required. |
| `Sine_Engine.maxpat` | Eight sine oscillators, one per sensor. |
| `Karplus_Strong_Engine.maxpat` | Dual coupled feedback delay engine. |
| `DataInput_Arduino.ino` | Arduino Mega firmware. Reads 8 load cells and sends data over USB serial. |

---

## Hardware Requirements

- Arduino Mega
- 8 × load cell sensors (wired to the Arduino via HX711 amplifier boards)
- Latex membrane instrument (or any pressure surface connected to the load cells)
- Computer running Max/MSP 8

---

## Setup and Starting the Instrument

### Step 1 — Upload the Arduino firmware

Open `DataInput_Arduino.ino` in the Arduino IDE and upload it to the Arduino Mega. Once uploaded, the Arduino will continuously read all eight load cells and send the data over USB serial.

### Step 2 — Open the Max patches

Open `Input_Scaling.maxpat` first. This patch is always required — it handles the serial connection and distributes sensor data to the other patches via Max's `send` objects.

The engine patches (`Sine_Engine.maxpat` and `Karplus_Strong_Engine.maxpat`) can be opened at any point, before or after the input patch. There is no required order. Once the input patch is running and receiving data, any open engine patch will receive it automatically.

### Step 3 — Configure the serial connection

In `Input_Scaling.maxpat`:

1. Select the correct **serial port** — the one the Arduino Mega is connected to.
2. Set the **baud rate** to **28800**.

### Step 4 — Tare the sensors (set the baseline)

Pressing the **Start button** in `Input_Scaling.maxpat` starts the data stream. During the first 10 values received, the patch automatically tares — it reads the resting state of the membrane and sets this as the baseline. **Do not apply any pressure to the membrane during this time.**

If a new tare is needed at any point during a session:

1. Turn the **Tare toggle** on.
2. Wait while the data is processed.
3. Turn the **Tare toggle off** — the new baseline is set at this moment.

---

## Running the Sine Engine

1. Open `Sine_Engine.maxpat`.
2. Turn on **audio processing** in Max (the speaker icon in the Max toolbar, or `Cmd+/`).
3. Select a tuning system from the options in the patch.

Each of the eight sensors controls the frequency and volume of one sine oscillator. A `slide~` object smooths the sensor data before it reaches the oscillators. The scaling range for each sensor can be adjusted, which effectively changes the tuning.

---

## Running the Karplus-Strong Engine

1. Open `Karplus_Strong_Engine.maxpat`.
2. Turn on **audio processing** in Max if not already on.
3. Click the **large toggle in the centre of the patch** to unmute the audio output.
4. Optionally select one of the two **compressor presets** to change the response character of the engine.

The engine consists of two dual feedback delay loops, each slightly different and driven by different sensor data streams. Inside each loop, the signal is amplified and passed through a low-pass filter before feeding back. A five-band multiband compressor (OMX5band) on the feedback path controls the dynamic range across frequency bands. The input exciter — a noise signal — is gated by the output level of the loop, so the engine re-excites automatically when the feedback drops below threshold.

---

## Notes

- `Input_Scaling.maxpat` is always required. The engine patches receive no data without it.
- The Karplus-Strong engine was developed from a dual feedback delay technique demonstrated by Edo Paulus in a Max/MSP live coding session (2009).
- Patches were developed in Max/MSP 8. Compatibility with earlier versions is not guaranteed.

---

## Author

David Bilek — Institute of Sonology, Royal Conservatoire, The Hague, 2026
