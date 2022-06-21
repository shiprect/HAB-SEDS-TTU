#ifndef SERVO_H
#define SERVO_H


#include <Arduino.h>
#if TEENSY_ENABLE
	#include <PWMServo.h>
#endif


#include "../../Config.h"




class Servo
{
    private:
        //PWMServo ServoPWM;//FIXME::PWMServo Lib
		bool ServoStatus;
		int CurrPosition = 0;

    public:
        Servo () {};
        ~Servo() {};

		void Servo_Setup();

		void Servo_Status(bool Status);
		void Servo_Move(uint8_t Position);

		void Servo_Update();
};

extern Servo CutServo;

#endif