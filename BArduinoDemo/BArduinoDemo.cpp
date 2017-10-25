#include <Arduino.h>

void setup() {
	pinMode(0, OUTPUT);
	pinMode(2, OUTPUT);
	Serial.begin(115200);
}

#define DELAY 400

static int n = 0;

void loop() {
	digitalWrite(0, HIGH);
	digitalWrite(2, LOW);
	delay(DELAY);

	digitalWrite(0, LOW);
	digitalWrite(2, HIGH);
	delay(DELAY);

	Serial.print(F("Hi EclipseCon! "));
	Serial.println(n++);
}
