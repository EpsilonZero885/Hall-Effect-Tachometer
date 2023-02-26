/* Libraries */
#include <Arduino.h>
/* 
Fix me! 
Try using a hardware interrupt to read the hall sensor inputs
*/

/* Global Variables */
const uint8_t sensor = 7;  // define the Hall magnetic sensor interface 
const uint8_t in3 = 4; //Control Right Motor (B)
const uint8_t in4 = 3; //Control Right Motor (B)
const uint8_t speedControlR = 9; //PWM Speed Control, Right Motor
bool val = LOW; //Used to store sensor reading

/* Setup loop */
void setup (){
    pinMode (sensor, INPUT) ; // define the Hall magnetic sensor line  as input
    pinMode (in3, OUTPUT); // Motor control pin, one high one low to send voltage from 12V source to motor
    pinMode (in4, OUTPUT); // Motor control pin, one high one low to send voltage from 12V source to motor
    pinMode (speedControlR, OUTPUT); //PWM pin for motor speed control 
    Serial.begin(9600); //Serial monitor
} //end setup()

/* Main Loop */
void loop () { 
    //Serial.print("  test1  "); // For testing
    digitalWrite(in3, HIGH); // Set a motor pin high
    digitalWrite(in4, LOW); // Set a motor pin low, motor starts
    analogWrite(speedControlR, 255); // Set motor speed, minimum for this worm motor is ~135, wow that noise is loud and annoying
    
    val=digitalRead(sensor); // read sensor, first time
    
    if (val == HIGH) { //If there is a magnetic field, this will be true; Starts counting rotations
        int ctr=0; //Define rpm counter variable
        uint16_t timeDatum=millis(); //set 0s datum
        uint16_t t1=0; //Define timer variable
        //Serial.print("  test2  "); // For testing
    
        while (t1<=5000) { //While our timer is below or equal 5s, this will be true
            val=digitalRead(sensor); // Read sensor

            if (val==HIGH){ //if there is a magnetic field, this will be true
                ctr=ctr+1; //count one full rotation
                //Serial.print("  test3  "); // For testing
                val=digitalRead(sensor); // Is the sensor still HIGH?
                                                
                while (val==HIGH) { //Wait until the sensor stops reading HIGH to avoid multiple counts of the same rotation
                    val=digitalRead(sensor);
                    //delay(1); // Add delay?
                    //Serial.print("  test4  "); // For testing
                } //end while (val == HIGH)    
            } //end if (val == HIGH)
                        
            t1=millis()-timeDatum; //Check the timer
        } //end while

        Serial.println(" ");
        Serial.print("Shaft Speed = ");
        Serial.print(ctr*12);
        Serial.println("rpm");
        //delay(5000);
    } //end if (val == HIGH)
} //end loop()

    
