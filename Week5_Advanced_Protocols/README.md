# Week 5: Advanced Protocols & DSP

## Overview
In the final week, we look at the bigger picture. We explore advanced connectivity with **OSC** (Open Sound Control) and polish our sound with time-based effects (Delay, Reverb). We also define the scope for the Final Project.

## Learning Objectives
- **OSC**: Sending/Receiving data over networks (introduction).
- Advanced DSP: Delay lines and Reverbs.
- optimizing performance.
- Final Project execution.

## 1. Open Sound Control (OSC)
OSC is a protocol for communication among computers, sound synthesizers, and other multimedia devices. It uses URL-style addressing.
*   Example: `/filter/cutoff 0.5`
*   **Daisy**: Typically uses UDP (over Wi-Fi if using ESP32 extension) or SLIP (Serial Line IP) over USB.

## 2. Time-Based Effects
*   **Delay**: Storing audio in a buffer and playing it back later.
    *   Feedback: Feeding the output back into the input.
*   **Reverb**: Simulating acoustic spaces (`ReverbSc` in DaisySP).

```cpp
DelayLine<float, 48000> delay; // 1 second buffer
// Callback:
delay.Write(in);
out = in + delay.Read();
```

## 3. Other Boards
*   **Teensy**: Powerful Cortex-M7. Great Audio Library (Design Tool).
*   **ESP32**: Built-in Wi-Fi/Bluetooth. Great for wireless OSC controllers.
*   **Arduino**: Good for simple MIDI controllers, less capable for DSP.

## 4. Final Project
Combine everything you've learned.
*   **Ideas**:
    *   A Granular Sampler.
    *   A Generative Ambient box.
    *   A UDP/OSC controller for Max/MSP or PureData.
    *   A multi-effects pedal for guitar.

---
**Congrats!** You have completed the introduction to Microcontrollers in Audio Design.
