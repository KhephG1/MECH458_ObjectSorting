# MECH 458 – Object Sorting System

ATmega2560-based mechatronic sorter that classifies and sorts four material types (steel, aluminium, white plastic, black plastic) on a conveyor + rotating bucket apparatus.

**Authors:** Khephren Gould & Clifton Tollefson  
**Course:** MECH 458 – Mechatronics (University of Victoria)

## Goal

Maximize the System Performance Index:

\[
SPI = \frac{N_c - N_i}{T_{MAX}}
\]

where \(N_c\) = correctly sorted objects, \(N_i\) = incorrectly sorted objects, and \(T_{MAX}\) is the allowed sorting time.

## System Overview

- **Conveyor** driven by a Banebots planetary gearmotor
- **Bucket** rotated by a Soyo unipolar stepper + L298
- **Sensors**
  - Optical (OR) – object detection mid-belt
  - Reflective (RL) – analog IR reflection for material classification
  - Optical gate (EX) – object at drop point
  - Hall effect (HE) – bucket home / position reference

Objects are classified via thresholding on the reflective sensor, stored in a FIFO linked-list queue, then dropped into the correct bucket partition.

## Software Architecture

Finite-state machine with the following states:

- Idle
- Reflective (classify + enqueue)
- Bucket (rotate + dequeue)
- Pause
- Error / Ramp-down

Control logic is written in C for the ATmega2560.

## Build (assumes CMake is installed)

```bash
mkdir build && cd build
cmake ..
make
