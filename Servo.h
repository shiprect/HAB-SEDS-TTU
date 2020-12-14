#ifndef __SERVO_H__
#define __SERVO_H__


#include <Arduino.h>
#include <PWMServo.h>


#include "config.h"
#include "debugutils.h"
#include "hardwareutils.h"




class Servo
{
    private:
        PWMServo ServoPWM;
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