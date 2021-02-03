#ifndef __STATUS_H__
#define __STATUS_H__


#include "../BMP/BMP.hpp"
#include "../GPS/GPS.hpp"
//#include "accel.hpp"
//#include "../SD_Card/SD_card.hpp"
#include "../SERVO/Servo.hpp"

#include "../../ProjectConfig.hpp"
#include "../utilities/utilities.h"

//#define lift_check_T 50
//#define burn_check_T 50
//#define apo_check_T 50
//#define fall_check_T 50
//#define liftoff_Gforce_check 6
//#define burnout_Gforce_check 3
//#define apogee_velocity_check 2.5 //check should be about 2.5 m/s



class Status {
    private:
        bool Rising = 0;
        bool Falling = 0;
		bool Landed = 0;
        
        bool ValidBMP = 0;
        bool ValidSD = 0;
		
		bool ServoStatus = OFF;
		
		bool WhatStatus = 0;
        
        void CheckSensors();
        
        void CheckRising();
        void CheckFalling();
		void CheckLanded();
		
		void CheckAPRS();

    public:
        Status() {};
        ~Status() {};
        
        void CheckStatus();
		void CheckServo();
        
		bool IsValidBMP();
        bool IsValidSD();
		
        bool IsRising();
        bool IsFalling();
		bool IsLanded();
		
        bool IsServoOn();
		
		bool WhatIsStatus();
};

extern Status status;


#endif
