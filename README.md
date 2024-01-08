# Adafruit QT Py M0 PlatformIO Project

This is a PlatformIO project for the Adafruit QT Py M0 board. The project is set up to help you get started with your Adafruit QT Py M0 and includes a basic example sketch in the `main.cpp` file.

## Prerequisites

Before you begin, make sure you have the following:

- [PlatformIO](https://platformio.org/install) installed on your computer.

## Getting Started

1. Clone or download this repository to your local machine.

2. Open the project folder in PlatformIO.

3. Connect your Adafruit QT Py M0 board to your computer.

4. Build and upload the firmware to the board using PlatformIO's built-in tools. You can do this by clicking the "Upload" button in the PlatformIO toolbar or by running the following command in the terminal:

   ```bash
   pio run -t upload

# Main.cpp for Adafruit QT Py M0 Environmental Monitor

This is the main.cpp file for an environmental monitoring project using an Adafruit QT Py M0 board. This project measures temperature, humidity, pressure, and accelerometer data from an MPU6050 sensor and displays it on an OLED screen. It also includes a buzzer that activates when the temperature exceeds a certain threshold.

## Dependencies

This project relies on several libraries that should be installed in your PlatformIO environment. These libraries include:

- Adafruit Sensor Library
- Adafruit BME280 Library
- Adafruit MPU6050 Library
- Adafruit GFX Library
- Adafruit SSD1306 Library
- Wire Library
- SPI Library

Make sure you have these libraries installed in your project's `platformio.ini` file under the `lib_deps` section.

## Hardware Setup

1. Connect your Adafruit QT Py M0 board to the necessary sensors and components.
2. Ensure the BME280 sensor, MPU6050 sensor, OLED display, and buzzer are connected correctly.

## Usage

1. Open this folder in PlatformIO.
2. Connect your Adafruit QT Py M0 board to your computer.
3. Build and upload the firmware to the board using PlatformIO's built-in tools.
4. Open the serial monitor to interact with your Adafruit QT Py M0.

## Functionality

- The code initializes the necessary sensors and components in the `setup()` function.
- It reads temperature, humidity, pressure, and accelerometer data from the BME280 and MPU6050 sensors.
- The data is displayed on an OLED screen.
- If the temperature exceeds a predefined threshold (`TEMP_THRESHOLD`), the buzzer will sound.
- Sensor data is also sent over the serial connection for monitoring and data logging.

Feel free to modify the code to fit your specific requirements or add additional features.



