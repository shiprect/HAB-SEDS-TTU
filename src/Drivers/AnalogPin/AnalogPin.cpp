#include "AnalogPin.hpp"


bool ANALOGPIN::ANALOGPIN_Setup() {
	pinMode( analogPin, INPUT );
}

bool ANALOGPIN::ANALOGPIN_Update() {
	// read the value from the sensor:
	analogValue = analogRead( analogPin );
	return true;
}


uint8_t ANALOGPIN::getAnalogValue() {
	return analogValue;
}
