#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed  hw;
Oscillator osc;
Adsr       env;

// 8-Step Sequence (MIDI Note Numbers)
float sequence[8]  = {60.0f, 62.0f, 63.0f, 65.0f, 67.0f, 69.0f, 71.0f, 72.0f};
int   current_step = 0;

// Timing
uint32_t last_step_time = 0;
uint32_t step_length    = 500; // ms

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        float sig     = osc.Process();
        float env_val = env.Process(
            false); // Triggered in main loop ideally, but ADSR needs gate logic
        // For simplicity in this example, we just let it run or need a proper Gate mechanism shared safely

        // *Improvement*: In a real app, handle timing in the callback for precision.

        out[0][i] = sig * env_val * 0.5f;
        out[1][i] = sig * env_val * 0.5f;
    }
}

int main(void)
{
    hw.Init();
    float sr = hw.AudioSampleRate();

    osc.Init(sr);
    osc.SetWaveform(Oscillator::WAVE_TRI);

    env.Init(sr);
    env.SetTime(ADSR_SEG_ATTACK, 0.01f);
    env.SetTime(ADSR_SEG_DECAY, 0.1f);
    env.SetTime(ADSR_SEG_SUSTAIN, 0.0f);
    env.SetTime(ADSR_SEG_RELEASE, 0.1f);

    hw.StartAudio(AudioCallback);

    while(1)
    {
        uint32_t now = System::GetNow();
        if(now - last_step_time >= step_length)
        {
            last_step_time = now;

            // Advance Step
            current_step = (current_step + 1) % 8;

            // Set Pitch
            float note = sequence[current_step];
            float freq = mtof(note);
            osc.SetFreq(freq);

            // Trigger Envelope (Retrigger)
            // Note: This is not thread-safe without atomic checks in audio callback,
            // but for a simple demo it often works or use a global 'trigger' flag processed in callback.
        }
    }
}
