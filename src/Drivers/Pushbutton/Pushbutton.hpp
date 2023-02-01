#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__

#include <Arduino.h>
#include "../../../Config.h"

//TODO::PUSHBUTTON Should have both Update check function, and also have an interrupt based version that is configurable
// All of this is not verified and should be tested to see if it actually works, including proper debounce
class PUSHBUTTON {
    private:

        bool ValidPUSHBUTTON;

			// Debouncing Variables:
		int buttonState;             // the current reading from the input pin
		int lastButtonState = LOW;   // the previous reading from the input pin
		float voltage;
		// the following variables are unsigned longs because the time, measured in
		// milliseconds, will quickly become a bigger number than can be stored in an int.
		unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
		unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
		const int buttonPin = 9; // trying D9 as of 20 june 2022
		// D13 on board, connected to the momentary PushButton (onboard led??)


    public:
        PUSHBUTTON () {};
        ~PUSHBUTTON() {};

        void PUSHBUTTON_Setup();
        void PUSHBUTTON_Update();

        bool IsValidPUSHBUTTON();
        float GetVoltage();
		// int GetledState();
		int GetbuttonState();
		int GetlastButtonState();

};

extern PUSHBUTTON pushbutton;


#endif