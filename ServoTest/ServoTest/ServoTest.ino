// Robotics with the BOE Shield - ForwardLeftRightBackward
// Move forward, left, right, then backward for testing and tuning.

#include <Servo.h>                           // Include servo library

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(2);                      // Attach left signal to P13 
  servoRight.attach(3);                     // Attach right signal to P12

  // Full speed forward
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(1000);                               // ...for 2 seconds

  servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach(); 
}  

void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
} 
