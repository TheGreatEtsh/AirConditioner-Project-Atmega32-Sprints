# AirConditioner-Project-Atmega32-Sprints
This project is the third project for the Automotive boot camp organized by Sprints, this project is developed by Team 6

## Team Members
- Ahmed Mohamed Hesham
- Momen Hassan
- Ahmed Atef

## About Project 
This project is developing software for temperature sensor integrated with ATMEGA32, 3*3 keypad, and LCD to make some functionalities similar to what happens with ACs.

So basically, the user will adjust the temperature he/she desires and the MC will compare it with the actual temperature and it buzzes if the actual temperature is higher than the desired temperature.

It consists of four layers:
### 1- APP 
This layer is responsible for integrating application modules and peripherals to perform project functionality via using their APIs
 
### 2- ECUAL
In this layer modules' drivers are developed which are the keypad's driver, temperature sensor's driver, and LCD driver.

This layer is like a middle junction between the application layer and the microcontroller abstraction layer

### 3- MCAL
In this layer, peripherals' drivers are developed: DIO's driver, timers' driver, and ADC.

### 4- SERVICE
This layer consists of files.h which will serve the main three layers while developing, like it has important data types' type defs, and bit manipulation macros like functions.

---
