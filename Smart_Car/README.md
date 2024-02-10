# Smart Car
![Smart Car](https://github.com/AssemAyman/Mastering-Embedded-System-Online-Diploma/assets/107751300/2b8e5234-fa4e-42f3-a28f-22ed5eb6e31a)

A mobile application controls the car via a Bluetooth module (HC-05). Also, an Ultrasonic sensor is used to avoid collisions.


# Mobile App:
![Mobile App](https://github.com/AssemAyman/Mastering-Embedded-System-Online-Diploma/assets/107751300/17fa517f-aaf7-40b4-91ff-0d7f44178fa0)

### Controls:-
1. Circle        -> Stop
2. Triangle      -> Horn
3. Square        -> Back Right
4. X             -> Back Left
5. Up Arrow      -> Forward
6. Down Arrow    -> Backward
7. Righ Arrow    -> Move Right
8. Left Arrow    -> Move Left

# Schematic:
![Schematic](https://github.com/AssemAyman/Mastering-Embedded-System-Online-Diploma/assets/107751300/50e0e53f-0609-4d1d-8628-3e13b01d97dd)

### Components:-
1. STM32F103C6T8
2. Motor Driver L298N
3. Bluetooth module HC-05
4. Ultrasonic Sensor
5. Car Chassis
6. Buzzer
7. Batteries

# Test Cases:
1. Test Case 1: Free Driving.
2. Test Case 2: If the car is already moving forward and it faces an obstacle in a range <= 30 CM it should stop.
3. Test Case 3: If the car is not moving and there is an obstacle in a range <= 30 CM, if the driver wants to move forward the car shall not move.
   
**To watch the demonstration video of these test cases press [here](https://drive.google.com/file/d/1FSzWr5nOK277A6aLxLW0w2PQ-fO9cMTV/view?usp=drive_link)**
