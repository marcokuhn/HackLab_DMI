#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hw;

// 1 second of delay at 48kHz
DelayLine<float, 48000> del;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        // Mono input from left channel
        float dry = in[0][i];

        // Read from delay line
        float wet = del.Read();

        // Write to delay line (Feedback loop: Input + 50% Feedback)
        del.Write(dry + (wet * 0.5f));

        // Output Mix (50% Dry, 50% Wet)
        out[0][i] = (dry * 0.5f) + (wet * 0.5f);
        out[1][i] = (dry * 0.5f) + (wet * 0.5f);
    }
}

int main(void)
{
    hw.Init();
    float sr = hw.AudioSampleRate();

    del.Init();
    del.SetDelay(sr * 0.5f); // 500ms Delay

    hw.StartAudio(AudioCallback);

    while(1)
    {
        System::Delay(100);
    }
}
