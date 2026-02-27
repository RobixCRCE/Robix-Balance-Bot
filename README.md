# Robix-Balance-Bot

Overview:
This project implements a basic proportional balancing system using two downward-facing ultrasonic sensors and a dual DC motor driver. The robot attempts to maintain equal ground distance on both sides by adjusting motor speeds.

Hardware Requirements:
Arduino Uno (or compatible board)
L298N or similar dual H-bridge motor driver
2 DC motors
2 Ultrasonic sensors (HC-SR04 type)
External motor power supply
Chassis and wiring

Pin Configuration:
Motor Driver
IN1 → 8
IN2 → 7
IN3 → 5
IN4 → 4
ENA → 11 (PWM)
ENB → 6 (PWM)

Ultrasonic Sensors:
Left Sensor
TRIG_L → 9
ECHO_L → 10

Right Sensor
TRIG_R → 2
ECHO_R → 3

Working Principle:
Both ultrasonic sensors measure ground distance.
The difference between left and right distances is treated as error.
A proportional controller adjusts motor speeds:
error = leftDist − rightDist
correction = error × gain
If both distances are within a defined threshold from the target height, motors stop.
Otherwise, motors adjust to reduce tilt.

Key Parameters:
targetDist = Desired ground distance (cm)
threshold = Dead zone for stopping
baseSpeed = Minimum movement speed
gain (30) = Proportional correction factor
These values must be tuned for your hardware.

Note:
Designed for Arduino boards supporting analogWrite().
Ultrasonic timeout set to 30 ms to avoid blocking.
Delay in loop (30 ms) may be adjusted for stability.
Use an external power source for motors.
