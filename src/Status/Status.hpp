#ifndef __STATUS_H__
#define __STATUS_H__

#include "../Drivers/BMP/BMP.hpp"
#include "../Drivers/GPS/GPS.hpp"
//#include "../Drivers/SD_Card/SD_card.hpp"
#include "../Drivers/SERVO/Servo.hpp"

#include "../../Config.h"


//TODO::Rework entire class, its never done what it should do well
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