# Raspberry Pi Pico Robot Control

This repository contains code for controlling a robot using a Raspberry Pi Pico. The code is written in MicroPython and includes functionality for controlling servos and a TM1637 display.

## Files

- `main.py`: Main script for controlling the robot.
- `servo_control.py`: Script for controlling the servos.
- `tm1637.py`: Script for controlling the TM1637 display.

## Requirements

- Raspberry Pi Pico
- MicroPython firmware
- TM1637 display
- Servos

## Installation

1. Flash the MicroPython firmware onto your Raspberry Pi Pico.
2. Copy the `main.py`, `servo_control.py`, and `tm1637.py` files to the Raspberry Pi Pico.

## Usage

1. Connect the TM1637 display and servos to the Raspberry Pi Pico.
2. Run the `main.py` script on the Raspberry Pi Pico.

## Functions

### `main.py`

- `cambiarModo()`: Change the mode of operation.
- `ejecutarModoManual()`: Execute manual mode.
- `ejecutarModoAutomatico()`: Execute automatic mode.
- `ejecutarModoUART()`: Execute UART mode.
- `evaluarModoActual()`: Evaluate the current mode of operation.
- `setServoAngle(servo, angle)`: Set the angle of a servo.
- `set0(theta0_desired)`: Set the angle of servo 0.
- `set1(theta1_desired)`: Set the angle of servo 1.
- `set2(theta2_desired)`: Set the angle of servo 2.
- `set3(theta3_desired)`: Set the angle of servo 3.
- `goto_servo(theta0_desired, theta1_desired, theta2_desired)`: Move servos to desired angles.
- `openHand()`: Open the hand.
- `closeHand()`: Close the hand.
- `openGate()`: Open the gate.
- `closeGate()`: Close the gate.

### `servo_control.py`

- `detenerMovimiento()`: Stop the movement.
- `setServoAngle(servo, angle)`: Set the angle of a servo.
- `set0(theta0_desired)`: Set the angle of servo 0.
- `set1(theta1_desired)`: Set the angle of servo 1.
- `set2(theta2_desired)`: Set the angle of servo 2.
- `set3(theta3_desired)`: Set the angle of servo 3.
- `goto_servo(theta0_desired, theta1_desired, theta2_desired)`: Move servos to desired angles.
- `openHand()`: Open the hand.
- `closeHand()`: Close the hand.
- `openGate()`: Open the gate.
- `closeGate()`: Close the gate.

### `tm1637.py`

- `tm1637initialise(tris, portPins, portLatch, dataBit, clkBit, displayType, brightness)`: Initialize the TM1637 display.
- `tm1637output(outputInteger, decimalPos, round, ldgZeroBlank, rightShift)`: Output an integer on the display.
- `tm1637UpdateDisplay()`: Update the display.
- `tm1637DisplayOn()`: Turn on the display.
- `tm1637DisplayOff()`: Turn off the display.
- `tm1637StartCondition()`: Send the start condition.
- `tm1637StopCondition()`: Send the stop condition.
- `tm1637ByteWrite(bWrite)`: Write one byte.
- `getDigits(number)`: Extract decimal digits from an integer.
- `roundDigits(numberToRemove)`: Round digits.
- `rightShiftDigits(rightShift)`: Shift digits to the right.
