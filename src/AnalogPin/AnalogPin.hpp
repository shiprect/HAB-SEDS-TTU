#ifndef __ANALOGPIN_H__
#define __ANALOGPIN_H__

#include <Arduino.h>
#include "../../Config.h"


class ANALOGPIN {
    private:
		const int sensorPin = A1;// A1/D15 - green wire -  Sensor to earth, needs to be analog: A0-7 //TODO::Should be specified in class init and decontructed appropriately
		int sensorValue = 0;  // variable to store the value coming from the sensor //TODO::Should have limited range based on pin reading, e.g. 0-255 for Arduino

    public:
        ANALOGPIN () {};
        ~ANALOGPIN() {};

        void ANALOGPIN_Setup();     //TODO::Should return true if  successful, false otherwise
        void ANALOGPIN_Update();    //TODO::Should return true if pin has been triggered
		int GetsensorValue();   //TODO::Should return uint in specified sensorValue range, sensorValue and function should be renamed for clarity
};

extern ANALOGPIN analogpin;

#endif