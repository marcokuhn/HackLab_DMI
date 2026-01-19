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


## 4. BASIC Examples

- Make you familiar with the DaisySP Reference e.g. Oscillator – [DaisySP Oscillator Reference](https://electro-smith.github.io/DaisySP/classdaisysp_1_1_oscillator.html)  
- Learn from examples > [Daisy Seed DSP Examples](https://github.com/electro-smith/DaisyExamples/tree/master/seed/DSP)

---

### 4.1 CONNECT LFO To Oscillator Amplitude 

**What is this?** An LFO (Low Frequency Oscillator) is a oscillator that modulates (changes) other parameters (< 40 Hz). In this example it changes the volume of the Oscillator. It creates a "wobbling" or "pulsing" effect - like someone turning a volume knob up and down very fast. The main oscillator generates the sound, and the LFO controls how loud it gets.

**Real-world example:** Think of a siren - the pitch stays the same but the volume goes up and down rhythmically.

```cpp
static Oscillator osc;      // Main audio oscillator (generates the tone)
static Oscillator lfo;      // LFO oscillator (very slow, controls amplitude)

static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float sig, lfo_mod, modulated_sig;
    
    for(size_t i = 0; i < size; i += 2)
    {
        // Generate the audio signal
        sig = osc.Process();
        
        // Generate the LFO signal (ranges from -1 to 1)
        // Shift and scale it to 0-1 range for amplitude control
        lfo_mod = (lfo.Process() + 1.0f) * 0.5f;  // Now ranges from 0 to 1
        
        // Multiply the audio signal by the LFO (modulate the amplitude)
        modulated_sig = sig * lfo_mod;
        
        // Output the modulated signal
        out[i] = modulated_sig;
        out[i + 1] = modulated_sig;
    }
}

// In main(), initialize both oscillators:
// Oscillator frequency = 550 Hz
// LFO freuqncy = 5 Hz
```

---

### 4.2 Chain modules (OSC → Filter → Out)

**What is this?** Signal chaining means sending the output of one module into the input of another. The audio flows through a chain: Oscillator → Filter → Output. A filter removes or emphasizes certain frequencies.

**Real-world example:** Like in a subtractive synth

```cpp
static Oscillator osc;      // Generates raw audio
static Svf filter;          // State Variable Filter (can cut or boost frequencies)

static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float osc_sig, filtered_sig;
    
    for(size_t i = 0; i < size; i += 2)
    {
        // Step 1: Generate the oscillator signal
        osc_sig = osc.Process();
        // Step 2: Create the chain OSC > Filter
        filtered_sig = filter.Process(osc_sig);
        
        // Create LowPass filter (Other SVF Filter options are High, Band, Notch, Peak )
        filtered_sig = filtered_sig.Low()

        // Step 3: Output the filtered signal
        out[i] = filtered_sig;
        out[i + 1] = filtered_sig;
    }
}

// In main(), 
// inittialize the oscillator: Frequency = 440Hz, Waveform = Sawtooth, Amplitude = 0.5
// initialize the filter: Frequency = 1000 Hz, Resonance = 0.6
```

---

### 4.3 Connect LFO to Filter Frequency (OSC → Filter → Out, LFO modulates Filter)

**What is this?** Instead of modulating amplitude like example 4.1, here the LFO controls the filter's cutoff frequency. This creates a sweeping, evolving sound where the filter opens and closes automatically. It's like the tone color is changing over time.

**Real-world example:** Subtractive synth with LFO`s

```cpp
static Oscillator osc;      // Main audio oscillator
static Oscillator lfo;      // LFO controls the filter cutoff
static Svf filter;          // The filter being modulated

static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float osc_sig, lfo_freq, filtered_sig;
    
    for(size_t i = 0; i < size; i += 2)
    {
        // Generate the audio signal
        osc_sig = osc.Process();
        
        // Generate the LFO signal and map it to filter frequency range
        // LFO ranges -1 to 1, map to 200-4000 Hz
        lfo_freq = (lfo.Process() + 1.0f) * 0.5f;  // change the range of the LFO from (-1,1) to (0,1) – Normalisation
        lfo_freq = 200.0f + (lfo_freq * 3800.0f);  // scale to Frequency Domain 200 to 4000 Hz
        
        // Update filter cutoff with LFO value
        filter.SetFreq(lfo_freq);
        
        // Process audio through the filter
        filtered_sig = filter.Process(osc_sig);
        
        // Output the result
        out[i] = filtered_sig.Low();
        out[i + 1] = filtered_sig.Low();
    }
}

// In main(), 
// inittialize the oscillator: Frequency = 600Hz, Waveform = Sawtooth, Amplitude = 0.5
// initialize the filter: Frequency = 1000 Hz, Resonance = 0.6
```

---

### 4.4 Mix signals together (Additive Synth with 5 Oscillators)

**What is this?** Additive synthesis builds complex tones by mixing multiple simple sine waves (oscillators) at different frequencies and amplitudes together. It's called "additive" because you ADD many simple signals. This is how professional synthesizers create rich, natural-sounding tones.

**Real-world example:** Additive synth

```cpp
// Create 5 oscillators to build a rich harmonic tone
static Oscillator osc1;     // Fundamental frequency (220 Hz - A3)
static Oscillator osc2;     // 1st harmonic (440 Hz - 2x fundamental)
static Oscillator osc3;     // 2nd harmonic (660 Hz - 3x fundamental)
static Oscillator osc4;     // 3rd harmonic (880 Hz - 4x fundamental)
static Oscillator osc5;     // 4th harmonic (1100 Hz - 5x fundamental)

static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float sig1, sig2, sig3, sig4, sig5, mixed;
    
    for(size_t i = 0; i < size; i += 2)
    {
        // Generate all 5 signals
        sig1 = osc1.Process() * 0.5f;   // Fundamental (strongest)
        sig2 = osc2.Process() * 0.3f;   // 2nd (weaker)
        sig3 = osc3.Process() * 0.2f;   // 3rd
        sig4 = osc4.Process() * 0.15f;  // 4th
        sig5 = osc5.Process() * 0.1f;   // 5th (weakest)
        
        // Mix them together
        mixed = sig1 + sig2 + sig3 + sig4 + sig5;
        
        // Normalize the Amplitude to prevent clipping (divide by the amount of the oscillators)
        mixed = mixed * 0.2f;  // Adjust overall volume
        
        // Output the rich, harmonic sound
        out[i] = mixed;
        out[i + 1] = mixed;
    }
}

// In main(), initialize all 5 oscillators with harmonic frequencies:
// osc1.Init(sample_rate);  osc1.SetFreq(220);   // Fundamental
// osc2.Init(sample_rate);  osc2.SetFreq(440);   // 2x
// osc3.Init(sample_rate);  osc3.SetFreq(660);   // 3x
// osc4.Init(sample_rate);  osc4.SetFreq(880);   // 4x
// osc5.Init(sample_rate);  osc5.SetFreq(1100);  // 5x
```

---