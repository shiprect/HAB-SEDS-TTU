#include "Pins.hpp"

void PINS::PINS_Setup() {
  pinMode(sensorPin, INPUT); 
}

void PINS::PINS_Update() {
  		 // read the value from the sensor:
		sensorValue = analogRead(sensorPin); 
					//DEBUG_PRINT(sensorValue);

}


int PINS::GetsensorValue() {  
    return sensorValue;
}