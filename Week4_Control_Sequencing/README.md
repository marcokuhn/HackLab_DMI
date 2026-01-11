# Week 4: Control & Sequencing

## Overview
A synthesizer needs to be played. This week focuses on external control. We will learn to read knobs (ADC), buttons (GPIO), and the standard language of electronic music: **MIDI**. We will also explore algorithmic playing via Sequencers.

## Learning Objectives
- Reading Analog Inputs (Potentiometers/Sensors).
- Digital Input debouncing (Switches).
- **MIDI Protocol** basics (Note On/Off, Control Change).
- Building a simple Step Sequencer.

## 1. Hardware Controls (ADC/GPIO)
*   **ADC (Analog to Digital Converter)**: Converts voltage (0-3.3V) to a float (0.0 - 1.0). Used for Knobs, Faders, Light sensors.
*   **GPIO Input**: Reads High/Low states. Used for buttons.

```cpp
// Initialize
adc.Init(inputs, 1); 
// Read
float cutoff_val = adc.GetFloat(0);
```

## 2. MIDI (Musical Instrument Digital Interface)
The universal language for synths. Daisy can communicate via USB MIDI or TRS MIDI (Hardware).
*   **Messages**: 3 bytes typically. `Status Byte | Data 1 | Data 2`.
    *   `Note On`: `0x90 | Note Number | Velocity`
    *   `Note Off`: `0x80 | Note Number | Velocity`

```cpp
MidiUsbHandler midi;
void HandleMidi() {
    midi.Listen();
    while(midi.HasEvents()) {
        auto msg = midi.PopEvent();
        if(msg.type == NoteOn) { /* Trigger Voice */ }
    }
}
```

## 3. Sequencing
A sequencer is just an array of notes played in a loop based on time.
*   **Clock**: We need a timer (Metronome).
*   **Step**: Current index in the array.

## 4. Project: MIDI Synth or Step Sequencer
**Option A (MIDI Synth)**: Connect your computer keyboard (or generic MIDI controller) via USB to the Daisy. Play notes on your Week 3 Synth.
**Option B (Sequencer)**: create an 8-step sequencer where the pitch is randomized or set by an array, and the speed is controlled by a knob.

---
**Assignment**:
1.  Add MIDI CC control to your Filter Cutoff.
2.  Implement a "Latch" mode for the sequencer.
