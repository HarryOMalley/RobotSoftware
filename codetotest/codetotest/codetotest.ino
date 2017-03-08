#include <Servo.h> // Include servo library
#include <EEPROM.h> // include EEPROM library to store variables in 'mini hardrive' and not in RAM
#include <time.h>


#define trigPinFront 5
#define echoPinFront 4
#define trigPinLeft 7
#define echoPinLeft 6
#define trigPinRight 9
#define echoPinRight 8
#define trigPinBack 11
#define echoPinBack 10
#define buttonPin 12



int resetState = 0;

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right, distance_back, duration_back, minimum_front = 7, minimum_back = 5, minimum_right = 15, minimum_left = 15, right_ir_sensor;
int front_stop;  // is this necessary?
int last_turn = 0;
long stop_t, start_t, final_t;
bool turned_left = false;
bool turned_right = false;

bool adjusted_before = false;
bool adjust = true;
long adj_timer_start = 0, adj_timer_end = 0, adj_timer_final = 0;


long temp_right_time;
long temp_left_time;

struct Choice {
	int add;
	long time = 0;
	bool state;
};

Choice left = {};
Choice right = {};

long x, y;

int re = 1;


void setup()
{
	Serial.begin(9600);
	// FOR CLEARING EPPROM

	checkForReset();

	//if (EEPROM.read(2) == 2) {
	//resetMemory(); 

	//}

	Serial.print("LEFT TIME:");
	Serial.print(EEPROM.read(0));
	Serial.print('\n');

	Serial.print("RIGHT TIME:");
	Serial.print(EEPROM.read(1));
	Serial.print('\n');

	Serial.print("LAST TURNED: ");
	Serial.print(EEPROM.read(2));
	Serial.print('\n');

	Serial.print("\n\n\n");

	turned_left = false;
	turned_right = false;

	right.add = 1;
	//int start_t = 0,  final_t = 0;



	// Sensor Setup
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(trigPinBack, OUTPUT);
	pinMode(echoPinBack, INPUT);
	//pinMode(buttonPin, INPUT);
	pinMode(A3, INPUT);


	// Servo Setup
	servoLeft.attach(2);                      // Attach left signal to P3
	servoRight.attach(3);                     // Attach right signal to P2

	servoLeft.attach(2);
	servoRight.attach(3);

	x = 1600;
	y = 1300;

	//dead_end();
	//turn_left();

	servoLeft.writeMicroseconds(x);         // Left wheel counterclockwise
	servoRight.writeMicroseconds(y);

	//turn_left(); 

	delay(2000);

	adjusted_before = false;
	adjust = true;

	adj_timer_start = 0, adj_timer_end = 0, adj_timer_final = 0;
	re = 1;
}

void loop()
{

	sensorRefresh(); // function that checks all the sensors
	Serial.print("DISTANCE BACK = ");
	Serial.print(distance_back);

	servoLeft.attach(2);
	servoRight.attach(3);
}



void sensorRefresh()
{

	//Serial.print("Refreshing sensor \n");
	// Ultra sound sensors
	digitalWrite(trigPinFront, LOW);
	digitalWrite(trigPinLeft, LOW);
	digitalWrite(trigPinRight, LOW);
	digitalWrite(trigPinBack, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPinFront, HIGH);
	digitalWrite(trigPinLeft, HIGH);
	digitalWrite(trigPinRight, HIGH);
	digitalWrite(trigPinBack, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPinFront, LOW);
	duration_front = pulseIn(echoPinFront, HIGH);
	distance_front = duration_front * (0.034 / 2);
	digitalWrite(trigPinLeft, LOW);
	duration_left = pulseIn(echoPinLeft, HIGH);
	distance_left = duration_left * (0.034 / 2);
	digitalWrite(trigPinRight, LOW);
	duration_right = pulseIn(echoPinRight, HIGH);
	distance_right = duration_right * (0.034 / 2);
	digitalWrite(trigPinBack, LOW);
	duration_back = pulseIn(echoPinBack, HIGH);//200000
	distance_back = duration_back * (0.034 / 2);


	//Infrared sensors
	right_ir_sensor = analogRead(A3);

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
}

void checkForReset()
{
	resetState = digitalRead(buttonPin); // Read the state of the pin 
	if (resetState == 1) { resetMemory(); } // calls memory reset funciton 
	else {} // do nothing 
}

void resetMemory() // clears memory by writing 0s to all addresses. 
{
	for (int i = 0; i < EEPROM.length(); i++)
	{
		EEPROM.write(i, 0);
	}
}

void new_adjust_func()
{
	if (abs(distance_left - distance_right) > 3 and abs(distance_left - distance_right) < 15)
	{
		if (distance_left > distance_right)
		{
			y += 50;
			x -= 50;
			//if y >
		}
		else if (distance_left < distance_right)
		{
			x -= 50; y += 50;
		}
	}
}


void dead_end()
{
	// Attach servos again
	servoLeft.attach(2);
	servoRight.attach(3);
	// turn right
	servoLeft.writeMicroseconds(1700);
	servoRight.writeMicroseconds(1700);
	delay(1000);
	servoLeft.detach();
	servoRight.detach();
	delay(2000);

}

void turn_left()
{
	// Attach servos again
	servoLeft.attach(2);
	servoRight.attach(3);
	// turn left
	servoLeft.writeMicroseconds(1300);
	servoRight.writeMicroseconds(1300);
	delay(500);
	servoLeft.detach();
	servoRight.detach();
	start_t = millis();
	turned_right = true;
	delay(2000);
}

void turn_right()
{
	// Attach servos again
	servoLeft.attach(2);
	servoRight.attach(3);
	// turn right
	servoLeft.writeMicroseconds(1700);
	servoRight.writeMicroseconds(1700);
	delay(500);
	servoLeft.detach();
	servoRight.detach();
	delay(2000);

}

void auto_adjust() // adjust function if one of the walls is too close. Adjusts according to which wall is closest. 
{
	if (abs(distance_left - distance_right) > 3 and abs(distance_left - distance_right) < 8) {
		//sensorRefresh();
		//if(distance_front < minimum_front){return;}
		if (adjust == false) { adj_timer_start = millis(); adjusted_before = true; adjust = true; }
		else
		{
			adj_timer_end = millis();
			adj_timer_final = adj_timer_end - adj_timer_start;
			if (adj_timer_final > 3000) { adjust = true; adj_timer_start = millis(); }
			else { return; }
		}


		if ((distance_left > distance_right) and (adjust == true)) {

			//servoLeft.detach();
			//servoRight.detach();

			//servoLeft.attach(2);
			//servoRight.attach(3);

			//servoLeft.detach();
			//servoRight.detach();
			//delay(20);

			servoLeft.writeMicroseconds(1400);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1300);
			delay(40);
			servoLeft.detach();
			servoRight.detach();
			servoLeft.attach(2);
			servoRight.attach(3);
			servoLeft.writeMicroseconds(1600);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1300);
			delay(15);

			//adjust = false;
			//adjusted_before = false

		}
		else if ((distance_left < distance_right) and (adjust == true)) {

			//servoLeft.detach();
			//servoRight.detach();
			//delay(20);

			servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1600);
			delay(40);
			servoLeft.detach();
			servoRight.detach();
			Serial.print("Detatched, and adjusting");
			servoLeft.attach(2);
			servoRight.attach(3);
			servoLeft.writeMicroseconds(1600);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1300);
			delay(15);


			//adjust = false;
		}
	}
}

int turned_around()
{
	checkForReset();
	Serial.print("\n");
	sensorRefresh(); // function that checks all the sensors
	Serial.print("DISTANCE BACK = ");
	Serial.print(distance_back);

	if ((distance_back > minimum_back) and ((distance_left < minimum_left) or (distance_right < minimum_right))) { //or (distance_back == 0)
		Serial.print("Moving Forward 2!");
		servoLeft.attach(2);
		servoRight.attach(3);

		//Serial.print(EEPROM.read(2));

		servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
		servoRight.writeMicroseconds(1650);
		//delay(10);      // Right wheel clockwise

		//sensorRefresh();
		turned_around_adjust_func();
		//new_adjust_func();

	}
	else if ((distance_left > (minimum_left + 5)) and (distance_right > (minimum_right + 5)) and (distance_back > (minimum_front + 10))) {

		Serial.print("THE MAZE HAS FINSHED. OUT");
		Serial.print(turned_left);
		Serial.print(turned_right);
		re = 0;

	}




	//if (right_ir_sensor > 550)
	//{
	//servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
	//servoRight.writeMicroseconds(1700);
	//delay(550);

	////servoLeft.writeMicroseconds(1500);         // Left wheel counterclockwise
	////servoRight.writeMicroseconds(1500);
	////delay(1200);

	//servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
	//servoRight.writeMicroseconds(1500);
	//delay(300);

	// servoLeft.detach();
	// servoRight.detach();

	//delay(550);
	//servoLeft.writeMicroseconds(1500);         // Left wheel counterclockwise
	//servoRight.writeMicroseconds(1500);
	//delay(1200);
	//}

	//delay(1)    // question, does the delay actually make the wheels faster? Because more time going forward, as opposed to going through logic
	//}
	else { // else if there needs to be some intelligence involved
		   // Stop the robot

		Serial.println("Front too close 2");
		servoLeft.detach();
		servoRight.detach();

		delay(1000);
		sensorRefresh();

		// if right path open and left closed, turn right
		if ((distance_right > minimum_right) and (distance_left < minimum_left))
		{
			Serial.println("RIGHT PATH OPEN TURNING RIGHT");
			// Attach servos again
			servoLeft.attach(2);
			servoRight.attach(3);
			// turn right
			servoLeft.writeMicroseconds(1300);
			servoRight.writeMicroseconds(1300);
			delay(450);
			servoLeft.detach();
			servoRight.detach();
			delay(1000);
			//sensorRefresh();
		}

		// if left path clear and right closed, turn left
		else if ((distance_right < minimum_right) and (distance_left > minimum_left))
		{
			Serial.println("LEFT PATH OPEN TURNING LEFT");
			// Attach servos again
			servoLeft.attach(2);
			servoRight.attach(3);
			// turn left
			servoLeft.writeMicroseconds(1700);
			servoRight.writeMicroseconds(1700);
			delay(450);
			servoLeft.detach();
			servoRight.detach();
			delay(1000);
			//sensorRefresh();
		}

		// if both left and right are clear
		else if ((distance_right > minimum_right) and (distance_left > minimum_left))
		{
			last_turn = EEPROM.read(2);
			Serial.print(last_turn);

			if (last_turn == 0) // hasnt turned left or right already at T junction
			{

				Serial.print("hasnt turned left or righttttt");

				// Attach servos again
				servoLeft.attach(2);
				servoRight.attach(3);
				// turn left
				servoLeft.writeMicroseconds(1700);
				servoRight.writeMicroseconds(1700);
				delay(450);
				servoLeft.detach();
				servoRight.detach();
				//delay(240000);
				delay(2000);

				start_t = millis();
				left.state = true;
				turned_left = true;
			}

			else if (last_turn == 1)  // has turned left already at T junction
			{

				Serial.print("turned already left ");

				// Attach servos again
				servoLeft.attach(2);
				servoRight.attach(3);
				// turn right
				servoLeft.writeMicroseconds(1300);
				servoRight.writeMicroseconds(1300);
				delay(450);
				servoLeft.detach();
				servoRight.detach();
				delay(2000);
				start_t = millis();
				turned_right = true;
			}
			else if (last_turn == 2) // if it's turned both left and right, calculate quickest route
			{

				Serial.print("turned already left and right");

				temp_left_time = EEPROM.read(0);
				temp_right_time = EEPROM.read(1);

				if (temp_left_time > temp_right_time)
				{
					Serial.print("##Turning RIGHT because already turned both ways and right is quicker!!! ##");
					// Attach servos again
					servoLeft.attach(2);
					servoRight.attach(3);
					// turn right
					servoLeft.writeMicroseconds(1300);
					servoRight.writeMicroseconds(1300);
					delay(450);
					servoLeft.detach();
					servoRight.detach();

					delay(2000);

					start_t = millis();
					turned_right = true;


					//EEPROM.write(2,3 );

					// For clearing memory
					for (int i = 0; i < EEPROM.length(); i++) { EEPROM.write(i, 0); }

				}

				else
				{ // turn left
					Serial.print("##Turning LEFT because already turned both ways and LEFT is quicker!!! ##");
					// Attach servos again
					servoLeft.attach(2);
					servoRight.attach(3);
					// turn left
					servoLeft.writeMicroseconds(1700);
					servoRight.writeMicroseconds(1700);
					delay(450);
					servoLeft.detach();
					servoRight.detach();
					start_t = millis();
					turned_right = true;
					delay(2000);
					//delay(240000);
				}
			}
		}

		// if in dead end, turn around
		else if ((distance_right < minimum_right) and (distance_left < minimum_left) and (distance_back < minimum_front))
		{
			Serial.println("DEAD END");
			// Attach servos again
			servoLeft.attach(2);
			servoRight.attach(3);
			// turn right
			servoLeft.writeMicroseconds(1300);
			servoRight.writeMicroseconds(1300);
			delay(1000);
			servoLeft.detach();
			servoRight.detach();
			delay(2000);
		}
		else { Serial.print("LAST OPTION TROLOLOL"); }
	}

}



void turned_around_adjust_func()
{
	if (abs(distance_left - distance_right) > 3 and abs(distance_left - distance_right) < 8) {
		//sensorRefresh();
		//if(distance_front < minimum_front){return;}
		if (adjust == false) { adj_timer_start = millis(); adjusted_before = true; adjust = true; }
		else
		{
			adj_timer_end = millis();
			adj_timer_final = adj_timer_end - adj_timer_start;
			if (adj_timer_final > 3000) { adjust = true; adj_timer_start = millis(); }
			else { return; }
		}


		if ((distance_left > distance_right) and (adjust == true)) {

			//servoLeft.detach();
			//servoRight.detach();

			//servoLeft.attach(2);
			//servoRight.attach(3);

			//servoLeft.detach();
			//servoRight.detach();
			//delay(20);

			servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1600);
			delay(40);
			servoLeft.detach();
			servoRight.detach();
			servoLeft.attach(2);
			servoRight.attach(3);
			servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1600);
			delay(15);

			//adjust = false;
			//adjusted_before = false

		}
		else if ((distance_left < distance_right) and (adjust == true)) {

			//servoLeft.detach();
			//servoRight.detach();
			//delay(20);

			servoLeft.writeMicroseconds(1400);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1300);
			delay(40);
			servoLeft.detach();
			servoRight.detach();
			Serial.print("Detatched, and adjusting");
			servoLeft.attach(2);
			servoRight.attach(3);
			servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
			servoRight.writeMicroseconds(1600);
			delay(15);


			//adjust = false;
		}
	}
}

