#ifndef SERVO_H
#define SERVO_H

//TODO::Figure out servo library situation
//TODO::Ideally, our custom PWM functionality should be used with these
#include <Arduino.h>
#if TEENSY_ENABLE
	#include <PWMServo.h>
#endif


#include "../../Config.h"

//TODO::check libdefs std:: instances, for Will
// #include <cstddef>
// #include <cstdint>
// #include <cmath>
// #include <array>


//TODO::Class should include setup-defined limits for servo min-max position if appropriate
//TODO::Add getServoPosition()
//TODO::ServoStatus should be reworked, was just a quick and dirty solution,
// if code requires that a servo be moved on a time interval, that should use the timing struct and a SERVO ON/OFF bool
class Servo
{
    private:
        //PWMServo ServoPWM;//FIXME::PWMServo Lib
		bool ServoStatus;
		int CurrPosition = 0;

		//TODO::For sending a list of commands, Will likely needs to set this up
		// e.g. std::array<int16_t, 6> cmd = {1000, 1200, 1300, 1400, 1500, 1600}; can be passed to func to send to set of positions
		// at a configurable time interval
		//std::array<int16_t, N> ch_;
		//unsigned int interval = 0;

    public:
        Servo () {};
        ~Servo() {};

		void Servo_Setup();//TODO::should return true if setup successful, false otherwise

		void Servo_Status(bool Status);//TODO::should return true if successful, false otherwise
		void Servo_Move(uint8_t Position);//TODO::should return true if successful, false otherwise (e.g. position was outside servo limits)

		void Servo_Update();//TODO::This is from when HAB cutting was written the night before, the functionality here should not be in the lass, it should be at the function call and performed using Servo_Move()
};

extern Servo CutServo;

#endif