#include <Servo.h>                           // Include servo library

#define trigPinFront 13
#define echoPinFront 12
#define trigPinLeft 11
#define echoPinLeft 10
#define trigPinRight 9
#define echoPinRight 8
#define led 7
#define led2 6
#define led3 5

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;


void setup() {
	Serial.begin(9600);
	// Sensor Setup
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	/*pinMode(led, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);*/

	// Servo Setup
	servoLeft.attach(3);                      // Attach left signal to P3
	servoRight.attach(2);                     // Attach right signal to P2
}

void loop() {
	long durationFront, distanceFront, durationLeft, distanceLeft, durationRight, distanceRight;
	digitalWrite(trigPinFront, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPinFront, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPinFront, LOW);
	durationFront = pulseIn(echoPinFront, HIGH);
	distanceFront = (durationFront / 2) / 29.1;

	digitalWrite(trigPinLeft, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPinLeft, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPinLeft, LOW);
	durationLeft = pulseIn(echoPinLeft, HIGH);
	distanceLeft = (durationLeft / 2) / 29.1;

	digitalWrite(trigPinRight, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPinRight, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPinRight, LOW);
	durationRight = pulseIn(echoPinRight, HIGH);
	distanceRight = (durationRight / 2) / 29.1;

	//if (distance < 4) {  // This is where the LED On/Off happens
	//	digitalWrite(led, HIGH); // When the Red condition is met, the Green LED should turn off
	//	digitalWrite(led2, LOW);
	//	digitalWrite(led3, LOW);
	//}
	//else if (distance < 8)
	//{
	//	digitalWrite(led3, HIGH);
	//	digitalWrite(led2, LOW);
	//	digitalWrite(led, LOW);
	//}

	//else {
	//	digitalWrite(led, LOW);
	//	digitalWrite(led2, HIGH);
	//	digitalWrite(led3, LOW);
	//}

	// Serial Feedback

	if (distanceFront >= 200 || distanceFront <= 0) {
		Serial.println("Front Out of range");
	}
	else {
		Serial.print("Front: ");
		Serial.print(distanceFront);
		Serial.println(" cm");
	}
	if (distanceLeft >= 200 || distanceLeft <= 0) {
		Serial.println("Left Out of range");
	}
	else {
		Serial.print("Left: ");
		Serial.print(distanceLeft);
		Serial.println(" cm");
	}
	if (distanceRight >= 200 || distanceRight <= 0) {
		Serial.println("Out of range");
	}
	else {
		Serial.print("Right: ");
		Serial.print(distanceRight);
		Serial.println(" cm");
	}
	delay(200);

}