# Hall-Effect-Tachometer

Notes:
Arduino program for measuring the rpm of an unidentified DC motor using a hall effect sensor to measure rotation of a disc with an embedded magnet
For this project a custom mount was created in Fusion360 and 3D printed. 
Any mount may be used such that the rotation of the motor shaft causes a magnet to concentrically move about a central axis and trigger a hall sensor

v2 Update Notes: 
Changed the pinouts and code to use a hardware interrupt for reading hall triggers

Parts:
    Unidentified DC Motor with Worm Drive
    Arduino Nano v3
    Breadboard
    12VDC Power supply
    L298N DC Motor Driver Module
    Elegoo Linear and Analog Hall Sensor Module
    Misc Wires

Pinouts
    12VDC PSU       L298N       Arduino Nano        Hall        Motor
    DC+             12V         N/C                 N/C         N/C
    DC-             GND         GND                 GND         N/C
    N/C             5V          5V                  +           N/C
    N/C             N/C         D3                  DO          N/C
    N/C             ENA         N/C                 N/C         N/C
    N/C             IN1         N/C                 N/C         N/C
    N/C             IN2         N/C                 N/C         N/C
    N/C             IN3         D4                  N/C         N/C
    N/C             IN4         D5                  N/C         N/C
    N/C             ENB         D9                  N/C         N/C
    N/C             OUT1        N/C                 N/C         N/C
    N/C             OUT2        N/C                 N/C         N/C
    N/C             OUT3        N/C                 N/C         DC+
    N/C             OUT4        N/C                 N/C         DC-