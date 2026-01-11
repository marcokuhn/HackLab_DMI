#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed  hw;
Oscillator osc;
Svf        filter;
Adsr       env;

// Hardware Inputs
Switch button;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        // 1. Generate Signal
        float sig = osc.Process();

        // 2. Apply Envelope
        // You would typically drive this with a Gate input
        float env_val = env.Process(false); // Placeholder for gate

        // 3. Filter
        filter.Process(sig);
        sig = filter.Low();

        // 4. Output
        out[0][i] = sig * env_val;
        out[1][i] = sig * env_val;
    }
}

int main(void)
{
    hw.Init();
    float sr = hw.AudioSampleRate();

    // Init DSP
    osc.Init(sr);
    osc.SetWaveform(Oscillator::WAVE_SAW);
    osc.SetFreq(110.0f);

    filter.Init(sr);
    filter.SetFreq(500.0f);
    filter.SetRes(0.5f);

    env.Init(sr);
    env.SetTime(ADSR_SEG_ATTACK, 0.01f);
    env.SetTime(ADSR_SEG_DECAY, 0.1f);
    env.SetTime(ADSR_SEG_SUSTAIN, 0.5f);
    env.SetTime(ADSR_SEG_RELEASE, 0.2f);

    // Init GPIO
    // button.Init(hw.GetPin(28), 1000);

    hw.StartAudio(AudioCallback);

    while(1)
    {
        // Poll button (Debounce)
        // button.Debounce();
        // bool gate = button.Pressed();
        // Pass gate to AudioCallback via global or atomic
        System::Delay(1);
    }
}
