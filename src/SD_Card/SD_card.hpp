#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "../../config.h"
#include "../utilities/utilities.h"

#include "../BMP/BMP.hpp"
#include "../GPS/GPS.hpp"
#include "../Status/Status.hpp"

const int ChipSelectPin = BUILTIN_SDCARD;


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
