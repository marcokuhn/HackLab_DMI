# DESIGNING MUSICAL INSTRUMENTS

Welcome to the course repository for **DESIGNING MUSICAL INSTRUMENTS**. This 5-week course introduces the world of embedded audio programming, focusing on the **Electrosmith Daisy** ecosystem, while also touching upon Teensy, ESP32, and Arduino platforms.

## Course Overview

This hands-on hacklab explores the creative and technical possibilities of embedded audio
processing and human-computer interaction (HCI). The main focus is on the Daisy Seed
platform — a powerful, open-source system designed specifically for high-fidelity music and
sound applications.

Whether you're building synthesizers, effect units, or sample-based instruments, the Daisy Seed
gives you the tools to start prototyping immediately. Just connect via USB and upload code in
C++, Plugdata, or Max/MSP Gen~ — and start creating sound.

In addition to Daisy, we’ll talk also about Teensy board projects and ESP32/Arduino
microcontrollers for interactive interfaces. You'll learn how to design both the sonic and physical aspects of electronic instruments, combining code, sensors, and sound design.

- **Topics**:
  - Synthesis techniques and sound generation
  - Audio effects and real-time DSP processing
  - Sample-based playback and manipulation
  - Human-Computer Interaction using ESP32 / Arduino
  - Prototyping new musical instruments and sound interfaces

**Duration**: 5 Weeks (approx. 25 hours)  
**Target Level**: Beginner to Intermediate/Advanced  

## Who is it for?
Artists, developers, and students from media arts, music tech, interaction design, or electronic
engineering. Some experience with coding (Arduino or C++) is helpful, but not required. Curiosity
and a willingness to experiment are essential.

## Structure

The course is divided into 5 modules. Each module contains lecture notes, code examples, and a hands-on project.

| Week | Module | Focus |
| :--- | :--- | :--- |
| **01** | [Foundations](./Week1_Foundations) | Microcontroller basics, Toolchain setup, C++ Intro |
| **02** | [Daisy Audio Basics](./Week2_Daisy_Basics) | libDaisy, DaisySP, Audio Callbacks, Basic Waveforms |
| **03** | [Synthesis & Sound Design](./Week3_Synthesis) | Subtractive Synthesis, Filters, Envelopes, Modulation |
| **04** | [Control & Sequencing](./Week4_Control_Sequencing) | Potentiometers, MIDI In/Out, Step Sequencers |
| **05** | [Advanced Protocols](./Week5_Advanced_Protocols) | OSC, Advanced DSP Effects, Final Project |

## Prerequisites

- **Hardware**: 
  - [Electrosmith Daisy Seed](https://electro-smith.com/pages/the-daisy-seed)
  - Breadboard & Jumper Wires
  - Potentiometers (10k Linear), Switches/Buttons
  - Optional: Teensy 4.x, ESP32 Dev Module
- **Software**:
  - [VS Code](https://code.visualstudio.com/)
  - [Git](https://git-scm.com/)
  - [DaisyToolchain](https://github.com/electro-smith/DaisyToolchain)
  - [Plug Data](https://plugdata.org/)

- **Github EDU Program**:


## Getting Started

1. **Clone this repository**:
   ```bash
   git clone <repository_url>
   ```
2. **Setup the Environment**: Follow the instructions in [Week 1](./Week1_Foundations).
3. **Build your first example**: Navigate to `Week1_Foundations/Examples/01_Blinky` and build the project.

## Resources

- [DESIGNING MUSICAL INSTRUMENTS](https://github.com/marcokuhn/DMI)
- [BOARDS](https://github.com/marcokuhn/DMI/tree/main/Boards)
- [PROTOCOLS MIDI / OSC / HID](https://github.com/marcokuhn/DMI/tree/main/Protocols)
- [PLUGDATA](https://github.com/marcokuhn/plugdata)
- **MAX/MSP – OOPSY**:
  - [GETTING STARTED WITH OOPSY](https://daisy.audio/tutorials/oopsy-dev-env)
  - [INTRODUCTION / SETUP BY CYCLING74](https://cycling74.com/tutorials/oopsydaisy-patch-an-introduction)
- **DIY COMMUNITY PAGES**:
  - [INSTRUCTABLES](https://www.instructables.com/)
  - [ARDUINO PROCJECT HUB](https://projecthub.arduino.cc/)

- **HELPFUL LINKS**:
  - [An Introduction To Additive Synthesis by Sound On Sound](https://www.soundonsound.com/techniques/introduction-additive-synthesis)
  - [MIDI – NOTES – FREQUENCY](http://newt.phys.unsw.edu.au/jw/graphics/notes.GIF)





 


- [libDaisy Documentation](https://electro-smith.github.io/libDaisy/)
- [DaisySP Documentation](https://electro-smith.github.io/DaisySP/)
- [Open Sound Control (OSC)](https://opensoundcontrol.org/)
- [MIDI Specification](https://www.midi.org/specifications)

---
