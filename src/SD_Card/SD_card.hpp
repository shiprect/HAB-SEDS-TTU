#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "../../ProjectConfig.hpp"
#include "../utilities/utilities.h"

#include "../BMP/BMP.hpp"
#include "../GPS/GPS.hpp"
#include "../Status/Status.hpp"

const int ChipSelectPin = BUILTIN_SDCARD;

//TODO::Create sd record function in each class and create #ifdef calls here
class SD_card
{
    private:
        File dataFile;
        
        bool ValidSD = 0;
        
    public:
        SD_card () {};
        ~SD_card() {};
    
        void SD_Setup();
        void SD_Record();
        
        bool IsValidSD();
};

extern SD_card sd;

#endif
