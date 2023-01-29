#include "AnalogPin.hpp"


void ANALOGPIN::ANALOGPIN_Setup() {
	pinMode( sensorPin, INPUT );
}

void ANALOGPIN::ANALOGPIN_Update() {
	// read the value from the sensor:
	sensorValue = analogRead( sensorPin );
}


int ANALOGPIN::GetsensorValue() {
	return sensorValue;
}