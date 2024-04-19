---

# Smart 3-Phase Energy Meter

This project aims to develop a smart 3-phase energy meter using Arduino and NodeMCU. The meter collects data from AC voltage and current sensors for each phase, processes the data, and sends it to the Blynk cloud for visualization and monitoring.

## Overview

The project consists of two main components:

1. **Arduino Nano Energy Meter**: This component reads data from AC voltage and current sensors for each phase, calculates parameters such as real power, apparent power, power factor, and total energy consumption (kWh), and displays the data on an LCD screen. It also sends the data to the NodeMCU via serial communication.

2. **NodeMCU Data Sender**: The NodeMCU receives data from the Arduino Nano, processes it, and sends it to the Blynk cloud for real-time visualization. It communicates with the Arduino Nano using serial communication and utilizes the EmonLib library for energy monitoring.

## Components Used

- Arduino Nano
- NodeMCU ESP8266
- Current Transformers (CTs) for current measurement
- Voltage Transformers (VTs) for voltage measurement
- LCD Display (LiquidCrystal_I2C)
- Blynk IoT Platform
- EmonLib Library

## Installation and Setup

1. **Hardware Setup**: Connect the CTs and VTs to the Arduino Nano for voltage and current measurement. Connect the LCD display for visualizing data. Connect the NodeMCU to the Arduino Nano via serial communication.

2. **Software Setup**:
   - Upload the Arduino Nano code to the Arduino board.
   - Upload the NodeMCU code to the NodeMCU board.
   - Install the necessary libraries (EmonLib, LiquidCrystal_I2C, SoftwareSerial, Blynk) using the Arduino Library Manager.

3. **Blynk Configuration**: Create a Blynk account and configure the Blynk app to receive data from the NodeMCU. Use the provided Blynk template ID and authorization token to link the app with the project.

## Usage

1. Power on the system.
2. The Arduino Nano starts reading data from the sensors and displays it on the LCD screen.
3. The NodeMCU receives the data from the Arduino Nano, processes it, and sends it to the Blynk cloud.
4. Open the Blynk app on your smartphone to visualize and monitor the energy consumption in real-time.

## Contributing

Contributions to the project are welcome! If you'd like to contribute, please fork the repository, make your changes, and submit a pull request. Be sure to follow the project's coding standards and guidelines.

## Credits

- Developed by [Your Name]
- Based on the EmonLib library by [Trystan Lea]
- Inspired by the Blynk IoT platform

---

Feel free to customize the README with additional details, such as wiring diagrams, screenshots, or specific instructions for setting up the hardware components.
