#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "TinyGPS++.h"

#include "config.h"
#include "debugutils.h"


class GPS
{
    private:
        TinyGPSPlus tinyGPS;
        SoftwareSerial GPSModule;
        bool valid_pos = false;
    
        void GPS_Debug();
    
    public:
        GPS ();
        ~GPS() {};

        void GPS_Setup();
        void GPS_Update();
        
        bool ValidLocation();
        int AgeLocation();

        double GetAltitude();
        double GetCourse();
        double GetSpeed();
        float GetLatitude();
        float GetLongitude();
        float GetFull_Latitude();
        float GetFull_Longitude();
        uint32_t GetDate();
        uint32_t GetSatellites();
        //uint32_t GetDate();
        uint8_t GetDay();
		uint8_t GetHour();
		uint8_t GetMinute();
		uint8_t GetSecond();

};

extern GPS gps;
//static GPS gps;

#endif
