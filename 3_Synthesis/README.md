# Week 3: Synthesis & Sound Design

## Overview
This week we move from simple tones to complex timbres. We will implement the building blocks of a Subtractive Synthesizer: Oscillators, Filters, and Envelopes. We will also introduce modulation using LFOs.

## Learning Objectives
- Understanding **Subtractive Synthesis**.
- Using the State Variable Filter (`Svf`).
- Controlling amplitude dynamics with Envelopes (`Adsr`).
- Modulation sources (`LFO`).

## 1. Subtractive Synthesis Architecture
The classic analog synth path:
`Source (Osc) -> Modifier (Filter) -> Output (VCA)`

## 2. The Filter (VCF)
Filters shape the sound by removing frequencies.
*   **Cutoff Frequency**: The point where attenuation begins.
*   **Resonance (Q)**: Emphasis at the cutoff point.
*   **Types**: Low Pass (LP), High Pass (HP), Band Pass (BP), Notch.

```cpp
Svf filter;
// In AudioCallback:
filter.Process(osc_signal);
out = filter.Low(); // Get Low Pass output
```

## 3. Envelopes (ADSR)
Sound isn't just constant volume. It has a shape.
*   **Attack**: Time to reach peak.
*   **Decay**: Time to drop to sustain level.
*   **Sustain**: Level held while note is active.
*   **Release**: Time to fade out after note end.

```cpp
Adsr env;
float amp = env.Process(gate_status);
out = signal * amp;
```

## 4. Project: MonoSynth
Build a synthesizer voice.
1.  **Oscillator**: Use a Saw or Square wave for rich harmonics.
2.  **Filter**: Add an LP filter after the oscillator.
3.  **VCA**: Control the final volume with an ADSR envelope.
4.  **LFO**: Use a low-frequency oscillator to modulate the Filter Cutoff.

---
**Assignment**:
1.  Map a potentiometer to Filter Cutoff
2.  Map a second potentiometer to Filter Resonance.(https://daisy.audio/tutorials/_a4_Getting-Started-ADCs/)
3.  Trigger the envelope with a button press.

[Read Potentiometer]((https://daisy.audio/tutorials/_a4_Getting-Started-ADCs/))
[Get Button State](https://daisy.audio/tutorials/_a1_Getting-Started-GPIO/)
