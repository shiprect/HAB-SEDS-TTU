#ifndef __GPS_H__
#define __GPS_H__

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "TinyGPS++.h"

#include "../../Config.h"


//TODO::DEBUG_PRINT() should be reworked to use a custom DEBUG_GPS that can be macro toggled for this class
class GPS {
	private:
		TinyGPSPlus tinyGPS;
		SoftwareSerial GPSModule;

		double MaxAltitude = 0;

		bool valid_pos = false;

		void GPS_Debug();

	public:
		GPS( const uint8_t, const uint8_t );

		~GPS() {
		};

		void GPS_Setup();//TODO::should return true if successful, false otherwise
		void GPS_Update();//TODO::should return true if successful, false otherwise

		//TODO::Location validity(valid_pos) and age should be rethought and easily configured requirements, Appropriate values are project dependent
		bool ValidLocation();
		int AgeLocation();

		//TODO::Clean these up, They should return consistent types; Honestly, this all should be a POD struct reworked from the TinyGPS Lib , I think I did some excessive wrapping here
		double GetAltitude();
		double GetMaxAltitude();
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

extern GPS gps, gps2;

#endif