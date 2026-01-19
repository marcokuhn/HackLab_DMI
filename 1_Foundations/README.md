# Week 1: Foundations

## Overview
This week establishes the groundwork for embedded audio programming. We will understand what a microcontroller is, how it differs from a regular computer, and set up our development environment. We will also cover C++ essentials needed for the course.

## Learning Objectives
- Understanding Microcontrollers (MCU)
- Overview of platforms: **Daisy**, **Teensy**, **ESP32**, **Arduino**.
- Setting up the **DaisyToolchain** and VS Code.
- C++ Basics: Compilation, Variables, Functions, Classes.
- "Hello World" in the embedded world: **Blinky**.

## Compatibility Note
While we focus on the **Electrosmith Daisy Seed**, the concepts of C++ and GPIO control translate well to Teensy (via Teensyduino) and ESP32 (via ESP-IDF or Arduino).

## 1. Microcontroller Basics
A Microcontroller Unit (MCU) is a compact integrated circuit designed to govern a specific operation in an embedded system. Unlike a personal computer, it runs a single program in a loop.
*   **Real-time constraints**: For audio, we strictly need to process samples within a specific timeframe (latency).
*   **Peripherals**: GPIO (General Purpose Input/Output), ADC (Analog to Digital Converter), DAC (Digital to Analog Converter).

- **DAIZY**:
    - [DAIZY HARDWARE INTRODUCTION](https://daisy.audio/hardware/Seed/)
    - [DAIZY SEED PINOUT](https://daisy.nyc3.cdn.digitaloceanspaces.com/products/seed/Daisy_Seed_pinout-25.pdf)
    - [DAIZY CODING OPTIONS](https://daisy.audio/software/)

## 2. Setting Up C++ ENVIRONMENT
- [Getting Started with C++ Daisy](https://daisy.audio/tutorials/cpp-dev-env/)
- [GIT INTRODUCTION](https://rogerdudler.github.io/git-guide/)
- [INTRODUCTION TO GITHUB](https://github.com/skills/introduction-to-github?tab=readme-ov-file)

## 3. BLINK EXAMPLE via C++
The "Hello World" of electronics.
- See https://daisy.audio/tutorials/cpp-dev-env/#4-run-the-blink-example
- IMPORTANT: Before Deployment put Daisy in Bootloader mode (Hold BOOT, Press RESET, Release RESET, Release BOOT) 

TODO: Modify the blinking speed.

## 4. SOUND EXAMPLE via C++  
- Navigate to DaisyExamples and OPEN "DaisyExamples/seed/DSP/oscillator" via vsCode
- put Daisy in Bootloader mode (Hold BOOT, Press RESET, Release RESET, Release BOOT) 
- Launch the command palette with Ctrl+P on Windows or Cmd+P on macOS
- execute -> "task build_and_program_dfu"
- Listen
TODO: Change Default Pitch.

## 5. SOUND EXAMPLE via PLUGDATA
- Download and Open [oscillator.pd](https://github.com/marcokuhn/HackLab_DMI/blob/main/1_Foundations/Examples/Plugdata/oscillator.pd) via PLUGDATA
- Compile
    - Patch to export > Currently open Patch
    - Target Board: Pod
    - execute Flash

Toubbleshoothing: 
error Message: Library not loaded: @executable_path/../lib/libusb-1.0.0.dylib
Reason: mapped file has no cdhash, completely unsigned? Code has to be at least ad-hoc signed.
- execute in terminal: codesign --force --deep --sign - /Users/{yourUserName}/Documents/plugdata/Toolchain/bin/dfu-util

TODO: Change Default Pitch
TODO: Change Default Amplitude
TODO: Change Default Waveform - see [Reference](https://electro-smith.github.io/DaisySP/classdaisysp_1_1_oscillator.html) of [DaisySP](https://github.com/electro-smith/DaisySP)

## 6. START YOUR OWN PROJECT
- see – https://daisy.audio/tutorials/create-new-project/
- /helper.py create MyProjects/MyFirstProject --board seed

