#ifndef __BMP_H__
#define __BMP_H__

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "Adafruit_BMP085_U.h"

#include "config.h"
#include "debugutils.h"
#include "hardwareutils.h"


class BMP {
    private:
        Adafruit_BMP085_Unified BMPModule = Adafruit_BMP085_Unified(10085);
        
        bool ValidBMP;
        
        float BaselinePressure;
        float Pressure;
        float Temperature;
        float Altitude;
        float MaxAltitude;

    public:
        BMP () {};
        ~BMP() {};

        void BMP_Setup();
        void BMP_Update();
        
        bool IsValidBMP();
        
        float GetBaselinePressure();
        float GetPressure();
        float GetTemperature();
        float GetAltitude();
        float GetMaxAltitude();
};

extern BMP bmp;


#endif
