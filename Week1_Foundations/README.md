# Week 1: Foundations

## Overview
This week establishes the groundwork for embedded audio programming. We will understand what a microcontroller is, how it differs from a regular computer, and set up our development environment. We will also cover C++ essentials needed for the course.

## Learning Objectives
- Understanding Microcontrollers (MCU) vs Microprocessors (MPU).
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

## 2. Setting Up
1.  **Install VS Code**: The primary editor.
2.  **Install the Toolchain**:
    *   **Windows/Mac**: Use the [DaisyToolchain](https://github.com/electro-smith/DaisyToolchain) installer. It includes GCC (compiler), Make, and OpenOCD (debugger).
3.  **Test the install**: Run `make --version` in your terminal.

## 3. C++ Refresher
Embedded audio relies heavily on C++.
*   **Structure**: Header files (`.h`) for declarations, Source files (`.cpp`) for implementation.
*   **Classes**: We use classes to represent hardware components (e.g., `Switch`, `Led`, `Oscillator`).

### Example: A Simple Class
```cpp
class Led {
public:
    void Init() { /* Setup GPIO */ }
    void TurnOn() { /* Set High */ }
    void TurnOff() { /* Set Low */ }
};
```

## 4. First Project: Blinky
The "Hello World" of electronics.
1.  Go to `Examples/01_Blinky`.
2.  Open `main.cpp`. (See example code in the folder).
3.  **Compile**: Run `make`.
4.  **Flash**: Put Daisy in Bootloader mode (Hold BOOT, Press RESET, Release RESET, Release BOOT) and run `make program-dfu`.
5.  Observe the onboard LED blinking!

---
**Assignment**: Modify the blinking speed. Try to create a "heartbeat" pattern (double blink).
