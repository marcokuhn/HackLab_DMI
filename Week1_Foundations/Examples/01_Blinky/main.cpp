#include "daisy_seed.h"

using namespace daisy;

DaisySeed hw;

int main(void)
{
    // Initialize the Daisy Seed hardware
    hw.Init();

    while(1)
    {
        // Turn the LED on
        hw.SetLed(true);
        // Wait 500ms
        System::Delay(500);

        // Turn the LED off
        hw.SetLed(false);
        // Wait 500ms
        System::Delay(500);
    }
}
