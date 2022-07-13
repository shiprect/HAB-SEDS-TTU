#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "../../Config.h"

#include "../BMP/BMP.hpp"
#include "../GPS/GPS.hpp"
#include "../Status/Status.hpp"
#include "../Pushbutton/Pushbutton.h"
#include "../Pins/Pins.hpp"

// const int ChipSelectPin = 10; // pin D10 on Nano Every, connected to DI on SD card reader

//TODO::Is Needed???
const int CLK = 13; // pin D13/SCK grey wire - Clock pin
const int DO = 12; // Digital output pin - purple wire  - CIPO
const int DI = 11; // Digital input pin - blue wire  - COPI
const int CS = 10; //BUILTIN_SDCARD; // 10 in nano every Chip select pin - white wire
//TODO::Create sd record function in each class and create #ifdef calls here
class SD_card
{
    private:
        File dataFile;

        bool ValidSD = 0;
		Sd2Card card;
		SdVolume volume;
		SdFile root;

    public:
        SD_card () {};
        ~SD_card() {};

        void SD_Setup();
        void SD_Record();
		void SD_arrayPass(int *x, int array_Size); //FIXME::
	
		
        bool IsValidSD();
};

extern SD_card sd;

#endif