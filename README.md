# Microcontrollers in Audio Design (Audiodesign B.A.)

Welcome to the course repository for **DESIGNING MUSICAL INSTRUMENTS**. This 5-week course introduces the world of embedded audio programming, focusing on the **Electrosmith Daisy** ecosystem, while also touching upon Teensy, ESP32, and Arduino platforms.

## Course Overview

This course is designed to take you from C++ basics to creating your own digital musical instruments. We will cover synthesis, sampling, sequencing, and communication protocols.

**Duration**: 5 Weeks (approx. 25 hours)  
**Target Level**: Beginner to Intermediate/Advanced  

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
  - [Electrosmith Daisy Seed](https://www.electro-smith.com/daisy/daisy-seed)
  - Breadboard & Jumper Wires
  - Potentiometers (10k Linear), Switches/Buttons
  - Optional: Teensy 4.x, ESP32 Dev Module
- **Software**:
  - [VS Code](https://code.visualstudio.com/)
  - [Git](https://git-scm.com/)
  - [DaisyToolchain](https://github.com/electro-smith/DaisyToolchain)

## Getting Started

1. **Clone this repository**:
   ```bash
   git clone <repository_url>
   ```
2. **Setup the Environment**: Follow the instructions in [Week 1](./Week1_Foundations).
3. **Build your first example**: Navigate to `Week1_Foundations/Examples/01_Blinky` and build the project.

## Resources

- [libDaisy Documentation](https://electro-smith.github.io/libDaisy/)
- [DaisySP Documentation](https://electro-smith.github.io/DaisySP/)
- [Open Sound Control (OSC)](https://opensoundcontrol.org/)
- [MIDI Specification](https://www.midi.org/specifications)

---
