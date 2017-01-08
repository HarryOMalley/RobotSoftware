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
long durationFront, distanceFront, durationLeft, distanceLeft, durationRight, distanceRight, minimumFront = 10;
int frontStop;

void setup()
{
	//Serial.begin(9600);
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

void loop()
{


	// Serial Feedback
	servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
	servoRight.writeMicroseconds(1400);        // Right wheel clockwise
	delay(10);

	sensorRefresh();
	//Serial.print("Front: ");
	//Serial.print(distanceFront);
	//Serial.println(" cm");
	if (distanceFront < minimumFront)
	{
		Serial.println("Front too close");
		servoLeft.detach();
		servoRight.detach();

	}


}

void sensorRefresh()
{

	digitalWrite(trigPinFront, LOW);
	digitalWrite(trigPinLeft, LOW);
	digitalWrite(trigPinRight, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPinFront, HIGH);
	digitalWrite(trigPinLeft, HIGH);
	digitalWrite(trigPinRight, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPinFront, LOW);
	durationFront = pulseIn(echoPinFront, HIGH);
	distanceFront = (durationFront / 2) / 29.1;
	digitalWrite(trigPinLeft, LOW);
	durationLeft = pulseIn(echoPinLeft, HIGH);
	distanceLeft = (durationLeft / 2) / 29.1;
	digitalWrite(trigPinRight, LOW);
	durationRight = pulseIn(echoPinRight, HIGH);
	distanceRight = (durationRight / 2) / 29.1;

	delay(10);
}
int checkDistance()
{
	if (distanceFront < 5)
	{
		Serial.println("Front Out of range");
		return 1;
	}
	else
	{
		Serial.print("Front: ");
		Serial.print(distanceFront);
		Serial.println(" cm");
	}
	/*if (distanceLeft >= 200 || distanceLeft <= 0)
	{
		Serial.println("Left Out of range");
	}
	else
	{
		Serial.print("Left: ");
		Serial.print(distanceLeft);
		Serial.println(" cm");
	}
	if (distanceRight >= 200 || distanceRight <= 0)
	{
		Serial.println("Out of range");
	}
	else
	{
		Serial.print("Right: ");
		Serial.print(distanceRight);
		Serial.println(" cm");
	}*/
}

//servoLeft.attach(2);                      // Attach left signal to P13 
//servoRight.attach(3);                     // Attach right signal to P12
//
//										  // Full speed forward
//servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
//servoRight.writeMicroseconds(1300);        // Right wheel clockwise
//delay(1000);                               // ...for 2 seconds
//
//servoLeft.detach();                        // Stop sending servo signals
//servoRight.detach();

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


	//if (distanceFront >= 200 || distanceFront <= 0) {
	//	Serial.println("Front Out of range");
	//}
	//else {
	//	Serial.print("Front: ");
	//	Serial.print(distanceFront);
	//	Serial.println(" cm");
	//}
	//if (distanceLeft >= 200 || distanceLeft <= 0) {
	//	Serial.println("Left Out of range");
	//}
	//else {
	//	Serial.print("Left: ");
	//	Serial.print(distanceLeft);
	//	Serial.println(" cm");
	//}
	//if (distanceRight >= 200 || distanceRight <= 0) {
	//	Serial.println("Out of range");
	//}
	//else {
	//	Serial.print("Right: ");
	//	Serial.print(distanceRight);
	//	Serial.println(" cm");
	//}
	//delay(200);