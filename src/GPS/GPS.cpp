#include "GPS.hpp"


GPS::GPS() : GPSModule (GPS_TX_PIN_TO_TEENSY, GPS_RX_PIN_TO_TEENSY){
    TinyGPSPlus tinyGPS;
    SoftwareSerial GPSModule(GPS_TX_PIN_TO_TEENSY, GPS_RX_PIN_TO_TEENSY);
}


void GPS::GPS_Setup() {
    GPSModule.begin(GPS_BAUDRATE);
    DEBUG_PRINT(F("\nGPS setup successful"));
}


void GPS::GPS_Update() {
    //Get a valid position from the GPS
    valid_pos = false;
    uint32_t timeout = millis();

    do  {
        if (GPSModule.available())  {
            //GPS_ADV_DEBUG(F("\nGPS module was available"));
            valid_pos = true;
            
            while (GPSModule.available() > 0)  {
                tinyGPS.encode(GPSModule.read());
            }
            
            GPS_Debug();  
        }
    }  while ( ((millis() - timeout) < GPS_VALID_POS_TIMEOUT) && !valid_pos);

	#ifdef DEBUG_GPS_BASIC
		if (valid_pos) {
			DEBUG_GPS_BASIC(F("\nLAT (deg) =       ")); DEBUG_GPS_BASIC(tinyGPS.location.rawLat().deg); // Raw latitude in whole degrees
			DEBUG_GPS_BASIC(F("\nLNG (deg) =       ")); DEBUG_GPS_BASIC(tinyGPS.location.rawLng().deg); // Raw longitude in whole degrees
			DEBUG_GPS_BASIC(F("\nDate (ddmmyy) =   ")); DEBUG_GPS_BASIC(tinyGPS.date.value()); // Raw date in DDMMYY format (u32)
			DEBUG_GPS_BASIC(F("\nTime (hhmmsscc) = ")); DEBUG_GPS_BASIC(tinyGPS.time.value()); // Raw time in HHMMSSCC format (u32)
			DEBUG_GPS_BASIC(F("\nCourse (deg) =    ")); DEBUG_GPS_BASIC(tinyGPS.course.deg()); // Course in degrees (double)
			DEBUG_GPS_BASIC(F("\nSpeed (mps) =     ")); DEBUG_GPS_BASIC(tinyGPS.speed.mps()); // Speed in meters per second (double)
			DEBUG_GPS_BASIC(F("\nAltitude (m) =    ")); DEBUG_GPS_BASIC(tinyGPS.altitude.meters()); // Altitude in meters (double)
			DEBUG_GPS_BASIC(F("\nSatellites =      ")); DEBUG_GPS_BASIC(tinyGPS.satellites.value()); // Number of satellites in use (u32)   
		} else {
			DEBUG_GPS_BASIC(F("\nFailed GPS position fix\n"));
		}
	#endif
}


void GPS::GPS_Debug()  {
    #ifdef GPS_ADV_DEBUG
        if (tinyGPS.location.isUpdated()) {
            DEBUG_GPS_ADV(F("\nraw LAT = "));     DEBUG_GPS_ADV(tinyGPS.location.rawLat().negative ? "-" : "+");
            DEBUG_GPS_ADV(F("\ndeg LAT = "));     DEBUG_GPS_ADV(tinyGPS.location.rawLat().deg); // Raw latitude in whole degrees
            DEBUG_GPS_ADV(F("\nLAT = "));         DEBUG_GPS_ADV(tinyGPS.location.rawLat().billionths);// ... and billionths (u16/u32)
            DEBUG_GPS_ADV(F("\nraw LNG = "));     DEBUG_GPS_ADV(tinyGPS.location.rawLng().negative ? "-" : "+");
            DEBUG_GPS_ADV(F("\ndeg LNG = "));     DEBUG_GPS_ADV(tinyGPS.location.rawLng().deg); // Raw longitude in whole degrees
            DEBUG_GPS_ADV(F("\nLNG = "));         DEBUG_GPS_ADV(tinyGPS.location.rawLng().billionths);// ... and billionths (u16/u32)
        }
        if (tinyGPS.date.isUpdated()) {
            DEBUG_GPS_ADV(F("\nYEAR = "));        DEBUG_GPS_ADV(tinyGPS.date.year()); // Year (2000+) (u16)
            DEBUG_GPS_ADV(F("\nMONTH = "));       DEBUG_GPS_ADV(tinyGPS.date.month()); // Month (1-12) (u8)
            DEBUG_GPS_ADV(F("\nDAY = "));         DEBUG_GPS_ADV(tinyGPS.date.day()); // Day (1-31) (u8)
            DEBUG_GPS_ADV(F("\nDDMMYY = "));      DEBUG_GPS_ADV(tinyGPS.date.value()); // Raw date in DDMMYY format (u32)
        }
        if (tinyGPS.time.isUpdated()) {
            DEBUG_GPS_ADV(F("\nHOUR = "));        DEBUG_GPS_ADV(tinyGPS.time.hour()); // Hour (0-23) (u8)
            DEBUG_GPS_ADV(F("\nMINUTE = "));      DEBUG_GPS_ADV(tinyGPS.time.minute()); // Minute (0-59) (u8)
            DEBUG_GPS_ADV(F("\nSECOND = "));      DEBUG_GPS_ADV(tinyGPS.time.second()); // Second (0-59) (u8)
            DEBUG_GPS_ADV(F("\nCENTISECOND = ")); DEBUG_GPS_ADV(tinyGPS.time.centisecond()); // 100ths of a second (0-99) (u8)
            DEBUG_GPS_ADV(F("\nHHMMSSCC = "));    DEBUG_GPS_ADV(tinyGPS.time.value()); // Raw time in HHMMSSCC format (u32)
        }
        if (tinyGPS.speed.isUpdated()) {
            DEBUG_GPS_ADV(F("\ncKNOTS = "));      DEBUG_GPS_ADV(tinyGPS.speed.value()); // Raw speed in 100ths of a knot (i32)
            DEBUG_GPS_ADV(F("\nKNOTS = "));       DEBUG_GPS_ADV(tinyGPS.speed.knots()); // Speed in knots (double)
            DEBUG_GPS_ADV(F("\nMPH = "));         DEBUG_GPS_ADV(tinyGPS.speed.mph()); // Speed in miles per hour (double)
            DEBUG_GPS_ADV(F("\nMPS = "));         DEBUG_GPS_ADV(tinyGPS.speed.mps()); // Speed in meters per second (double)
            DEBUG_GPS_ADV(F("\nKMPH = "));        DEBUG_GPS_ADV(tinyGPS.speed.kmph()); // Speed in kilometers per hour (double)
        }
        if (tinyGPS.course.isUpdated()) {
            DEBUG_GPS_ADV(F("\ncDEG = "));        DEBUG_GPS_ADV(tinyGPS.course.value()); // Raw course in 100ths of a degree (i32)
            DEBUG_GPS_ADV(F("\nDEG = "));         DEBUG_GPS_ADV(tinyGPS.course.deg()); // Course in degrees (double)
        }
        if (tinyGPS.altitude.isUpdated()) {
            DEBUG_GPS_ADV(F("\nALT KM = "));      DEBUG_GPS_ADV(tinyGPS.altitude.kilometers()); // Altitude in kilometers (double)
            DEBUG_GPS_ADV(F("\nALT M = "));       DEBUG_GPS_ADV(tinyGPS.altitude.meters()); // Altitude in meters (double)
            DEBUG_GPS_ADV(F("\nALT CM = "));      DEBUG_GPS_ADV(tinyGPS.altitude.value()); // Raw altitude in centimeters (i32)
            DEBUG_GPS_ADV(F("\nALT MI = "));      DEBUG_GPS_ADV(tinyGPS.altitude.miles()); // Altitude in miles (double)
            DEBUG_GPS_ADV(F("\nALT FT = "));      DEBUG_GPS_ADV(tinyGPS.altitude.feet()); // Altitude in feet (double)
        }
        if (tinyGPS.satellites.isUpdated()) {
            DEBUG_GPS_ADV(F("\nSAT = "));         DEBUG_GPS_ADV(tinyGPS.satellites.value()); // Number of satellites in use (u32)
        }
        if (tinyGPS.hdop.isUpdated()) {
            DEBUG_GPS_ADV(F("\nHOZ DIM = "));     DEBUG_GPS_ADV(tinyGPS.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
        }
    #endif    
}


bool GPS::ValidLocation() {
    return tinyGPS.location.isValid();
}


int GPS::AgeLocation() {
    return tinyGPS.location.age();
}


/****** Functions to return GPS values ******/
double GPS::GetAltitude() {
    return tinyGPS.altitude.meters();
}


double GPS::GetCourse() {
    return tinyGPS.course.deg();
}


double GPS::GetSpeed() {
    return tinyGPS.speed.mps();
}


float GPS::GetLatitude() {
    return tinyGPS.location.lat();
}


float GPS::GetLongitude() {
    return tinyGPS.location.lng();  
}


float GPS::GetFull_Latitude() {
    return tinyGPS.location.rawLat().billionths;
    //return tinyGPS.location.rawLat();
    //return 0;
}

float GPS::GetFull_Longitude() {
    return tinyGPS.location.rawLng().billionths;
    //return tinyGPS.location.rawLng();
    //return 0;
}

uint32_t GPS::GetDate() {
    return tinyGPS.date.value();
}


uint32_t GPS::GetSatellites() {
    return tinyGPS.satellites.value();
}


//uint32_t GPS::GetDate() {
//    return tinyGPS.date.value();
//}

uint8_t GPS::GetDay() {
    return tinyGPS.date.day();
}

uint8_t GPS::GetHour() {
    return tinyGPS.time.hour();
}

uint8_t GPS::GetMinute() {
    return tinyGPS.time.minute();
}

uint8_t GPS::GetSecond() {
    return tinyGPS.time.second();
}
