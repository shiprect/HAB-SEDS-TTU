#ifndef __PINS_H__
#define __PINS_H__

#include <Arduino.h>
#include "../../Config.h"


class PINS {
    private:
		const int sensorPin = A1;// A1/D15 - green wire -  Sensor to earth, needs to be analog: A0-7
		int sensorValue = 0;  // variable to store the value coming from the sensor

    public:
        PINS () {};
        ~PINS() {};

        void PINS_Setup();
        void PINS_Update();
		int GetsensorValue(); 
};

extern PINS pins;

#endif