/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPinFront 5
#define echoPinFront 4
#define trigPinLeft 7
#define echoPinLeft 6
#define trigPinRight 9
#define echoPinRight 8
#define trigPinBack 11
#define echoPinBack 10


long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right, minimum_front = 7, minimum_right = 15, minimum_left = 15, right_ir_sensor,duration_back,distance_back;
int front_stop;  // is this necessary?
bool turned_left = false;
bool turned_right = false;


void setup() {
	Serial.begin(9600);
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
  pinMode(trigPinBack, OUTPUT);
  pinMode(echoPinRight, INPUT);
}

void loop() {
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
	distance_front = (duration_front / 2) / 29.1;
	digitalWrite(trigPinLeft, LOW);
	duration_left = pulseIn(echoPinLeft, HIGH);
	distance_left = (duration_left / 2) / 29.1;
	digitalWrite(trigPinRight, LOW);
	duration_right = pulseIn(echoPinRight, HIGH);
	distance_right = (duration_right / 2) / 29.1;
  digitalWrite(trigPinBack, LOW);
  duration_back = pulseIn(echoPinBack, HIGH);
  distance_back = (duration_back / 2) / 29.1;

	//Infrared sensors
	right_ir_sensor = analogRead(0);

	//delay(10);
	Serial.print("Front: ");
	Serial.print(distance_front);
	Serial.print(" Left: ");
	Serial.print(distance_left);
	Serial.print(" Right: ");
	Serial.println(distance_right);
  Serial.print(" Back: ");
  Serial.println(distance_back);
	delay(100);




}
