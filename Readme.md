# AVR Context Switching with FCFS Algorithm

This repository contains an example code for implementing context switching using the First-Come, First-Served (FCFS) algorithm on an AVR microcontroller (ATmega328P).

## Introduction

The code demonstrates a basic multitasking system where multiple tasks are executed in a sequential manner using the FCFS scheduling algorithm. Each task represents an LED blinking operation with different delay intervals.

## Hardware Requirements

To run this code, you will need the following:

- AVR microcontroller (ATmega328P)
- LEDs connected to the corresponding GPIO pins (PB0, PB1, PB2)
- Development board or a suitable circuit setup
- AVR programmer or a means to flash the microcontroller

## Usage

1. Connect the LEDs to the GPIO pins (PB0, PB1, PB2) on the microcontroller.

2. Flash the microcontroller with the provided code using an AVR programmer or your preferred method.

3. Once the code is uploaded, the LEDs will start blinking according to the defined tasks.

## Customize

You can modify the code to add or remove tasks as needed. Each task is represented by a function that performs a specific action. To add a new task, create a new task function and update the `MAX_TASKS` constant accordingly.

Additionally, you can adjust the LED pins and delay intervals in each task function to customize the blinking behavior.

