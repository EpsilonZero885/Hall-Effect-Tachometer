/* Libraries */
#include <Arduino.h>
/* 
v2
Measuring rpm at full voltage, 12V, 255 PWM
*/

/* Global Variables */
const uint8_t sensor = 3;  // define the Hall magnetic sensor interface 
const uint8_t in3 = 4; //Control Right Motor (B)
const uint8_t in4 = 5; //Control Right Motor (B)
const uint8_t speedControlR = 9; //PWM Speed Control, Right Motor
volatile int ctr = 0; //Used to count rotations
volatile int timeDatum; //Used to set 0s datum
volatile int t1; //Used to set our start time to 0

void count() {
    ctr++;
}

/* Setup loop */
void setup (){
    pinMode (sensor, INPUT) ; // define the Hall magnetic sensor line  as input
    attachInterrupt(digitalPinToInterrupt(sensor), count, FALLING); // attach interrupt to the Hall magnetic sensor line
    pinMode (in3, OUTPUT); // Motor control pin, one high one low to send voltage from 12V source to motor
    pinMode (in4, OUTPUT); // Motor control pin, one high one low to send voltage from 12V source to motor
    pinMode (speedControlR, OUTPUT); //PWM pin for motor speed control 
    Serial.begin(9600); //Serial monitor
} //end setup()

/* Main Loop */
void loop () { 
    /* Start motor */
    noInterrupts(); //Don't count while we start the motor
    digitalWrite(in3, HIGH); // Set a motor pin high
    digitalWrite(in4, LOW); // Set a motor pin low, motor starts
    analogWrite(speedControlR, 255); // Set motor speed, minimum for this worm motor is ~135, wow that noise is loud and annoying
    timeDatum=millis(); //set 0s datum
    t1=0; //set our start time to 0
    ctr=0; //set our start count at 0
    interrupts(); //start counting!

    /* Count rotations for a period of 5s */
    while (t1<=5000) {
        t1=millis()-timeDatum; //set our current time to the time since the datum
    } // end while (t1<=5000)

    /* Print RPM */
    noInterrupts(); //stop counting while we print
    int rpm = ctr * 12;
    Serial.print("RPM:"); //print "RPM"
    Serial.print("\t"); //print tab
    Serial.println(rpm); //print RPM
    ctr = 0; //reset counter for next loop
    interrupts(); //start counting again for next loop

} //end loop()

    
