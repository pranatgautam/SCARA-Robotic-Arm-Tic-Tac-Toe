# SCARA Robotic Arm Based Tic-Tac-Toe

A SCARA robotic arm based interactive game system that combines embedded systems, image processing, robotic arm control, and experimental game logic.

The project uses an ESP32-CAM to capture the game board and integrates a robotic arm for physical game-piece movement. Image-processing techniques are used to analyze the board, while the robotic system uses servo motors and an electromagnet-based end effector to perform physical moves.

---

## Overview

The objective of this project is to develop a robotic system capable of interacting with a human player through a physical board game.

The system combines:

* ESP32-CAM based image capture
* Image processing
* Experimental game logic
* SCARA robotic arm control
* Inverse kinematics
* Servo motor control
* PCA9685 PWM servo driver
* Electromagnet-based end effector
* TFT/IPS LCD display
* Custom hardware and mechanical components

---

## System Workflow

```text
Human Player
     │
     ▼
Physical Game Board
     │
     ▼
ESP32-CAM
     │
     ▼
Image Capture
     │
     ▼
Image Processing
     │
     ▼
Board State Detection
     │
     ▼
Experimental Game Logic
     │
     ▼
Robot Move
     │
     ▼
Inverse Kinematics
     │
     ▼
Servo Control
     │
     ▼
SCARA Robotic Arm
     │
     ▼
Electromagnet
     │
     ▼
Game Piece Placement
```

---

## Hardware

The project incorporates the following hardware:

* ESP32-CAM
* TFT / IPS LCD display
* PCA9685 PWM servo driver
* Servo motors
* Electromagnet
* Custom PCB
* Custom robotic arm chassis
* 3D-printed mechanical components

---

## Software & Technologies

* Arduino / Embedded C++
* ESP32
* MATLAB
* Image Processing
* RGB565 Image Data
* Inverse Kinematics
* I2C Communication
* PCA9685
* TFT_eSPI
* Git / GitHub

---

## Image Processing

The ESP32-CAM is used to capture images of the game board.

During development, MATLAB was used to process and analyze the captured image data, including RGB565 image data and board-region analysis.

The image-processing code and relevant examples are organized under the `matlab/` directory.

---

## Robotic Arm Control

The robotic system uses a SCARA-style robotic arm to move game pieces on the board.

The selected board position is converted into a physical target position, after which inverse kinematics is used to determine the required arm movement.

Servo motors are controlled using a PCA9685 PWM servo driver through I2C communication.

An electromagnet is used at the end effector for handling the game pieces.

---

## Experimental Game Logic

The project includes experimental game logic for determining the robot's response to the human player's moves.

The game logic was developed specifically for the physical robotic system and is integrated with the board-state detection and robotic movement pipeline.

---

## Display

A TFT/IPS LCD display is used as part of the system interface.

The display configuration was developed around the ST7789 display controller and SPI communication.

---

## Repository Structure

```text
SCARA-Robotic-Arm-Tic-Tac-Toe/
│
├── firmware/
│   ├── main/
│   ├── camera/
│   ├── display/
│   └── control/
│
├── matlab/
│   ├── image_processing/
│   └── sample_images/
│
├── hardware/
│   ├── pcb/
│   └── schematics/
│
├── mechanical/
│   └── CAD/
│
├── documentation/
│
├── images/
│
└── README.md
```

---

## Project Highlights

* Physical human-robot interaction
* Camera-based board observation
* Image-processing based board analysis
* Experimental game logic
* SCARA robotic arm
* Inverse kinematics
* PCA9685 based servo control
* Electromagnet-based game-piece handling
* TFT/IPS LCD interface
* Custom electronics and mechanical design

---

## Project Status

This repository contains the source code, development files, and documentation associated with the SCARA robotic arm based game project.

Some components of the original development environment may depend on Arduino/ESP32 libraries and hardware-specific configurations.

---

## Author

**Pranat Gautam**

Embedded Systems | Robotics | Electronics

