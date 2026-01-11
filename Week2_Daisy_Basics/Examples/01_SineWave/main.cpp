#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed  hw;
Oscillator osc;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        // Get the next sample from the oscillator
        float sig = osc.Process();

        // Send to both Left and Right channels
        out[0][i] = sig;
        out[1][i] = sig;
    }
}

int main(void)
{
    // Initialize hardware
    hw.Init();
    hw.SetAudioBlockSize(4); // Typical block size
    float sample_rate = hw.AudioSampleRate();

    // Initialize Oscillator
    osc.Init(sample_rate);
    osc.SetWaveform(Oscillator::WAVE_SIN);
    osc.SetFreq(440.0f); // A4
    osc.SetAmp(0.5f);

    // Start Audio
    hw.StartAudio(AudioCallback);

    while(1)
    {
        // Main loop does nothing, audio runs in background interrupt
        System::Delay(100);
    }
}
