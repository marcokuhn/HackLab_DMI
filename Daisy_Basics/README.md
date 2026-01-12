# Week 2: Audio Programming Basics & The Daisy Platform

## Overview
Now that we have a working environment, we dive into generating sound. We will explore `libDaisy` (hardware abstraction) and `DaisySP` (signal processing). We will learn about the Audio Callback, the heartbeat of any real-time audio application.

## Learning Objectives
- Understanding the **Audio Callback**.
- Buffer Size and Sample Rate.
- Introduction to `DaisySP`.
- Generating a basic waveform (Sine Wave).

## 1. The Audio Architecture
Physical sound is continuous (analog). Computers work with discrete steps (digital).
*   **Sample Rate**: How many times per second we measure/output the signal (e.g., 48000 Hz).
*   **Bit Depth**: The resolution of each measurement (e.g., 16-bit, 24-bit).
*   **Block Size (Buffer Size)**: To be efficient, we process samples in chunks (blocks) rather than one by one. Typical sizes: 4, 16, 32, 64 samples.

## 2. The Audio Callback
The processor interrupts your main loop to ask for more audio data. If you don't provide it in time, you get a "glitch" or "dropout".

```cpp
void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        // DSP goes here!
        out[0][i] = 0.0f; // Left Silence
        out[1][i] = 0.0f; // Right Silence
    }
}
```

## 3. DaisySP
Electro-smith provides a DSP library.
*   **Oscillator**: `Oscillator osc;`
*   **Filter**: `Svf filter;`
*   **Effects**: reverb, delay, etc.

## 4. Project: Sine Wave
We will generate a pure tone.
1.  Initialize the Daisy hardware.
2.  Set up the Oscillator object (Frequency, Waveform, Amplitude).
3.  In the callback, call `osc.Process()` and send the result to the output.

### Code Sneak Peek
```cpp
float sig = osc.Process();
out[0][i] = sig;
out[1][i] = sig;
```

---
1.  Change the frequency of the oscillator.
2.  Try different waveforms (Saw, Square, Triangle).
3.  Add a second oscillator and mix them together.
