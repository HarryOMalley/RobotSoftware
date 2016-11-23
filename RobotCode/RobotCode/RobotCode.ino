#include <Servo.h>

#define trigPinFront 13
#define echoPinFront 12
#define trigPinLeft 11
#define echoPinLeft 10
#define trigPinRight 9
#define echoPinRight 8


#define led 7
#define led2 6
#define led3 5

void setup() {
	Serial.begin(9600);
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(led, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
}

void loop() {
	long duration, distance;
	digitalWrite(trigPin, LOW);  // Added this line
	delayMicroseconds(2); // Added this line
	digitalWrite(trigPin, HIGH);
	//  delayMicroseconds(1000); - Removed this line
	delayMicroseconds(10); // Added this line
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;
	if (distance < 4) {  // This is where the LED On/Off happens
		digitalWrite(led, HIGH); // When the Red condition is met, the Green LED should turn off
		digitalWrite(led2, LOW);
		digitalWrite(led3, LOW);
	}
	else if (distance < 8)
	{
		digitalWrite(led3, HIGH);
		digitalWrite(led2, LOW);
		digitalWrite(led, LOW);
	}

	else {
		digitalWrite(led, LOW);
		digitalWrite(led2, HIGH);
		digitalWrite(led3, LOW);
	}
	if (distance >= 200 || distance <= 0) {
		Serial.println("Out of range");
	}
	else {
		Serial.print(distance);
		Serial.println(" cm");
	}
	delay(100);
}