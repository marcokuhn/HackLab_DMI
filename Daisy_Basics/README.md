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

## 2. Basic Program Structure

This program demonstrates the fundamental structure of a Daisy audio application. It generates a continuous 440 Hz sine wave tone (the musical note A4) and outputs it to both left and right audio channels.

### Key Components:

1. **Hardware Object (`DaisySeed hw`)**: Manages all communication with the physical Daisy Seed board, including audio I/O, sample rate, and buffer management.

2. **Oscillator Object (`Oscillator osc`)**: A DaisySP module that generates audio waveforms. It can produce sine, sawtooth, square, and triangle waves at specified frequencies and amplitudes.

3. **Audio Callback Function**: The heart of real-time audio processing. This function is called automatically by the hardware at regular intervals (12,000 times per second with our settings) to fill the audio buffer with new samples.

4. **Main Function**: Runs once at startup to:
   - Initialize the hardware
   - Configure the oscillator parameters (waveform type, frequency, amplitude)
   - Start the audio engine
   - Keep the program alive with an infinite loop

### Program Flow:

```
Startup → Initialize Hardware → Configure Oscillator → Start Audio Engine → 
→ [AudioCallback runs continuously in background] → Infinite Loop
```

The AudioCallback processes audio in small chunks (blocks) rather than one sample at a time for efficiency. With a block size of 4 samples and a sample rate of 48,000 Hz, each callback processes 4 samples and is called 12,000 times per second, resulting in ultra-low latency (0.083 ms).

```cpp
// example adopted from https://github.com/electro-smith/DaisyExamples/blob/master/seed/DSP/oscillator/oscillator.cpp

// Include the DaisySP library - provides DSP modules like oscillators, filters, effects
#include "daisysp.h"
// Include the Daisy Seed library - handles hardware communication and audio I/O
#include "daisy_seed.h"

// These lines let us use classes without typing "daisysp::" or "daisy::" every time
using namespace daisysp;
using namespace daisy;

// Create a hardware object to control the Daisy Seed board
// 'static' means this variable lives for the entire program duration
static DaisySeed  hw;

// Create an oscillator object that will generate our audio signal
static Oscillator osc;

// This is the AUDIO CALLBACK FUNCTION - it runs automatically at high priority
// to fill the audio buffer with samples. This gets called many times per second! (SampleRate / BlockSize)
// Parameters:
//   in   - input buffer (audio coming into the Daisy)
//   out  - output buffer (audio going out of the Daisy)
//   size - number of samples to process (this includes both left and right channels)
static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    // Variable to store the audio signal from the oscillator
    float sig;
    
    // Loop through the buffer in steps of 2 because audio is STEREO
    // (i = left channel, i+1 = right channel)
    for(size_t i = 0; i < size; i += 2)
    {
        // Generate the next sample from the oscillator
        sig = osc.Process();

        // Send the signal to the left output channel
        out[i] = sig;

        // Send the same signal to the right output channel (mono to stereo)
        out[i + 1] = sig;
    }
}

// MAIN FUNCTION - the program starts here
int main(void)
{
    // STEP 1: Initialize the hardware
    // Variable to store the sample rate (samples per second, e.g., 48000 Hz)
    float sample_rate;
    // Configure the Daisy Seed with default settings
    hw.Configure();
    // Initialize the hardware (sets up audio codec, clocks, pins, etc.)
    hw.Init();
    // Set how many samples to process at once (smaller = lower latency, higher CPU load)
    // Parameter 4 = 4 Samples 
    // Calculate Latency e.g. SampleRate = 48000; Latency = 1/48000 * 4 = 0.0000833 sec = 0.083 milliseconds (ms)    
    hw.SetAudioBlockSize(4);
    // Get the sample rate from the hardware (usually 48000 Hz)
    sample_rate = hw.AudioSampleRate();
    // Initialize the oscillator with the sample rate (needed for accurate frequency generation)
    osc.Init(sample_rate);

    // STEP 2: Configure the oscillator parameters
    // Set the waveform type to sine wave (smooth, pure tone)
    // Other options: WAVE_SAW, WAVE_SQUARE, WAVE_TRI, WAVE_POLYBLEP_SAW, etc.
    osc.SetWaveform(osc.WAVE_SIN);
    // Set the frequency to 440 Hz (the musical note A4)
    osc.SetFreq(440);
    // Set the amplitude to 0.1 (volume level: 0.0 = silent, 1.0 = full volume)
    // Lower values prevent clipping and protect your ears!
    osc.SetAmp(0.1);

    // STEP 3: Start the audio engine
    // Tell the hardware to start calling AudioCallback() automatically
    // The callback will run in the background to generate continuous audio
    // It will be called 12000 times per second (48000 / 4) (Samplerate / Blocksize)
    hw.StartAudio(AudioCallback);

    // STEP 4: Keep the program running
    // Infinite loop - the program stays alive here while AudioCallback runs in the background
    // Without this, the program would end and audio would stop!
    while(1) {}
}
```


## 3. DaisySP
DaisySP is an open-source DSP (Digital Signal Processing) library that provides a comprehensive collection of modular components for creating audio software across various contexts, facilitating the development of high-quality and customizable audio applications.
- [DasiySP](https://github.com/electro-smith/DaisySP)
- [DaisySP Reference](https://electro-smith.github.io/DaisySP/annotated.html)

e.g.
*   **Oscillator**: `Oscillator osc;`
*   **Filter**: `Svf filter;`
*   **Effects**: reverb, delay, etc.
+   **...**


## 4.BASIC Examples

- Make you familiar with the DaisySP Reference e.g. Oscillator – [DaisySP Oscillator Reference](https://electro-smith.github.io/DaisySP/classdaisysp_1_1_oscillator.html)  
- Learn from examples > [Daisy Seed DSP Examples](https://github.com/electro-smith/DaisyExamples/tree/master/seed/DSP)

### CONNECT LFO To Oscillator Amplitude 
### Chain modules (OSC + Filter)
### Connect LFO to Filter Frequency (OSC > Filter > Out)
### Mix signals together (Additive Synth with 5 Oscillator)

```cpp
// Example to mix 2 signals together
static Oscillator osc1;  // First oscillator
static Oscillator osc2;  // Second oscillator

static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float sig1, sig2, mixed;
    
    for(size_t i = 0; i < size; i += 2)
    {
        // Generate samples from both oscillators
        sig1 = osc1.Process();
        sig2 = osc2.Process();
        
        // Mix them together (add and scale)
        mixed = (sig1 + sig2) * 0.5f;
        
        // Output to both channels
        out[i] = mixed;
        out[i + 1] = mixed;
    }
}
```