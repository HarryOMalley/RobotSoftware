#include <Servo.h> // Include servo library
#include <EEPROM.h> // include EEPROM library to store variables in 'mini hardrive' and not in RAM

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
long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right, minimum_front = 7, minimum_right = 15, minimum_left = 15, right_ir_sensor;
int front_stop;  // is this necessary?
bool turned_left = false;
bool turned_right = false;

void setup()
{
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

void loop()
{
	sensorRefresh(); // function that checks all the sensors

					 //Serial.print("Front: ");
					 //Serial.print(distance_front);
					 //Serial.println(" cm");


	Serial.println("Started again!! ");

	Serial.println("RIGHT SENSOR: ");
	Serial.println(right_ir_sensor);

	// Serial Feedback


	if (distance_front > minimum_front) {
		servoLeft.attach(3);
		servoRight.attach(2);

		servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
		servoRight.writeMicroseconds(1300);        // Right wheel clockwise

												   //if(right_ir_sensor > 450){
												   //if (right_ir_sensor > 400){
												   //servoLeft.writeMicroseconds(1510);         // Left wheel counterclockwise
												   //servoRight.writeMicroseconds(1300);
												   //}

												   //servoLeft.writeMicroseconds(1575);         // Left wheel counterclockwise
												   //servoRight.writeMicroseconds(1300);
												   //delay(0.1);
												   //}
		if (right_ir_sensor > 550)
		{
			servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1700);
			delay(550);
			//servoLeft.writeMicroseconds(1500);         // Left wheel counterclockwise
			//servoRight.writeMicroseconds(1500);
			//delay(1200);
			servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1500);
			delay(300);

			servoLeft.detach();
			servoRight.detach();
			//delay(550);
			//servoLeft.writeMicroseconds(1500);         // Left wheel counterclockwise
			//servoRight.writeMicroseconds(1500);
			//delay(1200);
		}

		//delay(1)    // question, does the delay actually make the wheels faster? Because more time going forward, as opposed to going through logic
	}
	else { // else if there needs to be some intelligence involved
		   // Stop the robot
		Serial.println("Front too close");
		servoLeft.detach();
		servoRight.detach();

		Serial.print(turned_right);
		Serial.println(" RIGHT ");

		Serial.print(turned_left);
		Serial.println(" LEFT ");

		// if right path open and left closed, turn right
		if ((distance_right > minimum_right) and (distance_left < minimum_left))
		{
			// Attach servos again
			servoLeft.attach(3);
			servoRight.attach(2);
			// turn right
			servoLeft.writeMicroseconds(1700);
			servoRight.writeMicroseconds(1700);
			delay(550);
			servoLeft.detach();
			servoRight.detach();
			//delay(240000);
		}

		// if left path clear and right closed, turn left
		else if ((distance_right < minimum_right) and (distance_left > minimum_left))
		{
			// Attach servos again
			servoLeft.attach(3);
			servoRight.attach(2);
			// turn left
			servoLeft.writeMicroseconds(1300);
			servoRight.writeMicroseconds(1300);
			delay(600);
			servoLeft.detach();
			servoRight.detach();
			//delay(240000);
		}

		// if both left and right
		else if ((distance_right > minimum_right) and (distance_left > minimum_left))
		{

			if (turned_left == false and turned_right == false)
			{
				// Attach servos again
				servoLeft.attach(3);
				servoRight.attach(2);
				// turn left
				servoLeft.writeMicroseconds(1300);
				servoRight.writeMicroseconds(1300);
				delay(600);
				servoLeft.detach();
				servoRight.detach();
				//delay(240000);

				turned_left = true;
			}

			else if (turned_left == true and turned_right == false)
			{
				// Attach servos again
				servoLeft.attach(3);
				servoRight.attach(2);
				// turn right
				servoLeft.writeMicroseconds(1700);
				servoRight.writeMicroseconds(1700);
				delay(600);
				servoLeft.detach();
				servoRight.detach();
				turned_right = true;
			}
			else if (turned_left == true and turned_right == true)
			{
				// Attach servos again
				servoLeft.attach(3);
				servoRight.attach(2);
				// turn right
				servoLeft.writeMicroseconds(1700);
				servoRight.writeMicroseconds(1700);
				delay(600);
				servoLeft.detach();
				servoRight.detach();
				turned_right = true;
			}
		}

		// if in dead end, turn around
		else if ((distance_right < minimum_right) and (distance_left < minimum_left)) {
			// Attach servos again
			servoLeft.attach(3);
			servoRight.attach(2);
			// turn right
			servoLeft.writeMicroseconds(1700);
			servoRight.writeMicroseconds(1700);
			delay(1200);
			servoLeft.detach();
			servoRight.detach();
		}

	}
	//Serial.print("Front: ");
	//Serial.print(distanceFront);
	//Serial.println(" cm");
}


void sensorRefresh()
{


	// Ultra sound sensors
	digitalWrite(trigPinFront, LOW);
	digitalWrite(trigPinLeft, LOW);
	digitalWrite(trigPinRight, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPinFront, HIGH);
	digitalWrite(trigPinLeft, HIGH);
	digitalWrite(trigPinRight, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPinFront, LOW);
	duration_front = pulseIn(echoPinFront, HIGH);
	distance_front = (duration_front / 2) / 29.1;
	digitalWrite(trigPinLeft, LOW);
	duration_left = pulseIn(echoPinLeft, HIGH);
	distance_left = (duration_left / 2) / 29.1;
	digitalWrite(trigPinRight, LOW);
	duration_right = pulseIn(echoPinRight, HIGH);
	distance_right = (duration_right / 2) / 29.1;

	//Infrared sensors
	right_ir_sensor = analogRead(0);

	//delay(10);
}

int checkDistance() // Started coding fucntion to check distance - not currently used
{
	if (distance_front < 5)
	{
		Serial.println("Front Out of range");
		return 1;
	}
	else
	{
		Serial.print("Front: ");
		Serial.print(distance_front);
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
//                                                                                // Full speed forward
//servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
//servoRight.writeMicroseconds(1300);        // Right wheel clockwise
//delay(1000);                               // ...for 2 seconds
//
//servoLeft.detach();                        // Stop sending servo signals
//servoRight.detach();

//if (distance < 4) {  // This is where the LED On/Off happens
//      digitalWrite(led, HIGH); // When the Red condition is met, the Green LED should turn off
//      digitalWrite(led2, LOW);
//      digitalWrite(led3, LOW);
//}
//else if (distance < 8)
//{
//      digitalWrite(led3, HIGH);
//      digitalWrite(led2, LOW);
//      digitalWrite(led, LOW);
//}

//else {
//      digitalWrite(led, LOW);
//      digitalWrite(led2, HIGH);
//      digitalWrite(led3, LOW);
//}


//if (distanceFront >= 200 || distanceFront <= 0) {
//      Serial.println("Front Out of range");
//}
//else {
//      Serial.print("Front: ");
//      Serial.print(distanceFront);
//      Serial.println(" cm");
//}
//if (distanceLeft >= 200 || distanceLeft <= 0) {
//      Serial.println("Left Out of range");
//}
//else {
//      Serial.print("Left: ");
//      Serial.print(distanceLeft);
//      Serial.println(" cm");
//}
//if (distanceRight >= 200 || distanceRight <= 0) {
//      Serial.println("Out of range");
//}
//else {
//      Serial.print("Right: ");
//      Serial.print(distanceRight);
//      Serial.println(" cm");
//}
//delay(200);