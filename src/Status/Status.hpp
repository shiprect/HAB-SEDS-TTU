#ifndef __STATUS_H__
#define __STATUS_H__


#include "../BMP/BMP.hpp"
#include "../GPS/GPS.hpp"
//#include "accel.hpp"
//#include "../SD_Card/SD_card.hpp"
#include "../SERVO/Servo.hpp"

#include "../../ProjectConfig.hpp"
#include "../utilities/utilities.h"



class Status {
    private:
		uint64_t TimeSinceLaunch = 0;
		
		bool Launched = FALSE;
        bool Rising = FALSE;
        bool Falling = FALSE;
		bool Landed = FALSE;
        
        bool ValidBMP = FALSE;
        bool ValidSD = FALSE;
		
		bool ServoStatus = OFF;
        
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
		
		bool IsLaunched();
        bool IsRising();
        bool IsFalling();
		bool IsLanded();
		
        bool IsServoOn();
};

extern Status status;


#endif
