#ifndef __ACCEL_H__
#define __ACCEL_H__


#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <stdlib.h>
#include <stdio.h>
#define SS A6 // Serial Select -> CS on LIS331 
#define MOSI A3 // MasterOutSlaveIn -> SDI
#define MISO A4 // MasterInSlaveOut -> SDO
#define SCK A5 // Serial Clock -> SPC on LIS331 r

#include "config.h"
#include "debugutils.h"
#include "hardwareutils.h"

#define SCALE 0.0007324; // approximate scale factor for full range (+/-24g)
// scale factor: +/-24g = 48G range. 2^16 bits. 48/65536 = 0.0007324
using namespace std;
//turn 0;// global acceleration values


class ACCEL {
    private:    
        float x;
        float y;
        float z;  
        double xAcc;
        double yAcc;
        double zAcc;
        double accx;
        double accy;
        double accz;

    public:
        ACCEL () {};
        ~ACCEL() {};

        void ACCEL_Setup();
        void ACCEL_Update();
        
        //float GetSeaLevelPressure();
        //float GetPressure();
        //float GetTemperature();
        //float GetAltitude();
};

#endif
