# Smart Walking Stick for Visually Impaired

A smart walking stick that uses sensors to help visually impaired users navigate safely. It detects obstacles, water hazards, and potential falls, and alerts the user with a buzzer.

## Features

- **Ultrasonic Sensor**: Detects obstacles in front of the user.
- **Infrared Sensor**: Detects nearby obstacles for close-range safety.
- **Water Sensor**: Detects puddles or wet surfaces.
- **MPU6050 Accelerometer**: Detects sudden falls or tilts.
- **Buzzer Alert**: Alerts the user when any sensor is triggered.

## Components Used

- Arduino Nano
- MPU6050 Accelerometer
- Ultrasonic Sensor (HC-SR04)
- IR Sensor
- Water Sensor (SEN-18)
- Buzzer
- Jumper Wires
- Breadboard or PCB
- 3.3V/5V power supply

## Circuit Connections

### Arduino Nano

| Sensor / Module       | Arduino Pin |
|----------------------|------------|
| Ultrasonic TRIG       | D2         |
| Ultrasonic ECHO       | D3         |
| IR Sensor             | D4         |
| Water Sensor          | A0         |
| Buzzer                | D10        |
| MPU6050 SDA           | A4         |
| MPU6050 SCL           | A5         |
| MPU6050 VCC           | 3.3V       |
| MPU6050 GND           | GND        |

> Note: Use 10 kΩ pull-up resistors for SDA and SCL if using a bare MPU6050.

## Installation

1. Connect the hardware according to the circuit diagram above.
2. Install the required Arduino libraries:
   - `Wire.h`
   - `MPU6050.h` (available via Library Manager)
3. Upload the `SmartWalkingStick.ino` code to your Arduino Nano.
4. Open the Serial Monitor (9600 baud) to see sensor alerts.

## Usage

- When an obstacle, water, or fall is detected, the buzzer will sound.
- Adjust thresholds in the code (`OBSTACLE_DISTANCE`, `WATER_THRESHOLD`, `FALL_THRESHOLD`) for sensitivity.

## License

MIT License
