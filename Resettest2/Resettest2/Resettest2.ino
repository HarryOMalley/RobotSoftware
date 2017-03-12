#define buttonPin 12

int resetState = 0;         // variable for reading the pushbutton status

void setup() {
	// initialize the pushbutton pin as an input:
	pinMode(buttonPin, INPUT);
}

void loop() {

	resetState = digitalRead(buttonPin); // Read the state of the pin

	if (resetState == HIGH) 
	{
		resetMemory(); // If it is high, then call the reset function
	} // Else do nothing
	else
	{
		Serial.println("Im feeling low");
		delay(1000);
	}
}

void resetMemory()
{
	Serial.println("im really high rn");
	delay(1000);
}