# Nucleo-F429ZI FreeRTOS Task Example

This project provides a simple FreeRTOS task example for the STMicroelectronics Nucleo-F429ZI development board.

## How to Use

1.  **Generate a project with STM32CubeMX:**
    *   Open STM32CubeMX and create a new project for the Nucleo-F429ZI.
    *   In the "Pinout & Configuration" tab, configure a peripheral for output, like a GPIO pin for an LED.
    *   In the "Middleware" section, enable FreeRTOS.
    *   Generate the code for your preferred toolchain (e.g., STM32CubeIDE, Keil, IAR).

2.  **Replace `main.c`:**
    *   Replace the generated `main.c` file in your project's `Core/Src` or `Src` directory with the `main.c` file from this example.

3.  **Build and Flash:**
    *   Compile the project and flash it to your Nucleo-F429ZI board.
    *   You should see the tasks running (e.g., LEDs blinking).

