#include "GPS.hpp"


GPS::GPS( const uint8_t TX, const uint8_t RX ) : GPSModule( TX, RX ) {
	TinyGPSPlus tinyGPS;
}


void GPS::GPS_Setup() {
	GPSModule.begin( GPS_BAUDRATE );
	DEBUG_PRINT( F( "\nGPS setup successful" ));
}


void GPS::GPS_Update() {
	//Get a valid position from the GPS
	valid_pos = false;
	uint32_t timeout = millis();

	do {
		if ( GPSModule.available()) {
			//GPS_ADV_DEBUG(F("\nGPS module was available"));
			valid_pos = true;

			while ( GPSModule.available() > 0 ) {
				tinyGPS.encode( GPSModule.read());
			}

			if ( GetAltitude() > MaxAltitude ) {
				MaxAltitude = gps.GetAltitude();
			}
		}
	} while ((( millis() - timeout ) < GPS_VALID_POS_TIMEOUT ) && !valid_pos );

	if ( valid_pos ) {
		GPS_Debug();
	}
	else {
		//DEBUG_PRINT(F("\nFailed GPS position fix\n"));		//fix this; possibly remove
	}
}


void GPS::GPS_Debug() {
	#ifdef DEBUG_PRINT
	DEBUG_PRINT( F( "\nLAT (deg) =       " ));
	DEBUG_PRINT( tinyGPS.location.rawLat().deg ); // Raw latitude in whole degrees
	DEBUG_PRINT( F( "\nLNG (deg) =       " ));
	DEBUG_PRINT( tinyGPS.location.rawLng().deg ); // Raw longitude in whole degrees
	DEBUG_PRINT( F( "\nDate (ddmmyy) =   " ));
	DEBUG_PRINT( tinyGPS.date.value()); // Raw date in DDMMYY format (u32)
	DEBUG_PRINT( F( "\nTime (hhmmsscc) = " ));
	DEBUG_PRINT( tinyGPS.time.value()); // Raw time in HHMMSSCC format (u32)
	DEBUG_PRINT( F( "\nCourse (deg) =    " ));
	DEBUG_PRINT( tinyGPS.course.deg()); // Course in degrees (double)
	DEBUG_PRINT( F( "\nSpeed (mps) =     " ));
	DEBUG_PRINT( tinyGPS.speed.mps()); // Speed in meters per second (double)
	DEBUG_PRINT( F( "\nAltitude (m) =    " ));
	DEBUG_PRINT( tinyGPS.altitude.meters()); // Altitude in meters (double)
	DEBUG_PRINT( F( "\nSatellites =      " ));
	DEBUG_PRINT( tinyGPS.satellites.value()); // Number of satellites in use (u32)
	#endif

	#ifdef GPS_ADV_DEBUG
	if (tinyGPS.location.isUpdated()) {
		DEBUG_PRINT(F("\nraw LAT = "));     DEBUG_PRINT(tinyGPS.location.rawLat().negative ? "-" : "+");
		DEBUG_PRINT(F("\ndeg LAT = "));     DEBUG_PRINT(tinyGPS.location.rawLat().deg); // Raw latitude in whole degrees
		DEBUG_PRINT(F("\nLAT = "));         DEBUG_PRINT(tinyGPS.location.rawLat().billionths);// ... and billionths (u16/u32)
		DEBUG_PRINT(F("\nraw LNG = "));     DEBUG_PRINT(tinyGPS.location.rawLng().negative ? "-" : "+");
		DEBUG_PRINT(F("\ndeg LNG = "));     DEBUG_PRINT(tinyGPS.location.rawLng().deg); // Raw longitude in whole degrees
		DEBUG_PRINT(F("\nLNG = "));         DEBUG_PRINT(tinyGPS.location.rawLng().billionths);// ... and billionths (u16/u32)
	}
	if (tinyGPS.date.isUpdated()) {
		DEBUG_PRINT(F("\nYEAR = "));        DEBUG_PRINT(tinyGPS.date.year()); // Year (2000+) (u16)
		DEBUG_PRINT(F("\nMONTH = "));       DEBUG_PRINT(tinyGPS.date.month()); // Month (1-12) (u8)
		DEBUG_PRINT(F("\nDAY = "));         DEBUG_PRINT(tinyGPS.date.day()); // Day (1-31) (u8)
		DEBUG_PRINT(F("\nDDMMYY = "));      DEBUG_PRINT(tinyGPS.date.value()); // Raw date in DDMMYY format (u32)
	}
	if (tinyGPS.time.isUpdated()) {
		DEBUG_PRINT(F("\nHOUR = "));        DEBUG_PRINT(tinyGPS.time.hour()); // Hour (0-23) (u8)
		DEBUG_PRINT(F("\nMINUTE = "));      DEBUG_PRINT(tinyGPS.time.minute()); // Minute (0-59) (u8)
		DEBUG_PRINT(F("\nSECOND = "));      DEBUG_PRINT(tinyGPS.time.second()); // Second (0-59) (u8)
		DEBUG_PRINT(F("\nCENTISECOND = ")); DEBUG_PRINT(tinyGPS.time.centisecond()); // 100ths of a second (0-99) (u8)
		DEBUG_PRINT(F("\nHHMMSSCC = "));    DEBUG_PRINT(tinyGPS.time.value()); // Raw time in HHMMSSCC format (u32)
	}
	if (tinyGPS.speed.isUpdated()) {
		DEBUG_PRINT(F("\ncKNOTS = "));      DEBUG_PRINT(tinyGPS.speed.value()); // Raw speed in 100ths of a knot (i32)
		DEBUG_PRINT(F("\nKNOTS = "));       DEBUG_PRINT(tinyGPS.speed.knots()); // Speed in knots (double)
		DEBUG_PRINT(F("\nMPH = "));         DEBUG_PRINT(tinyGPS.speed.mph()); // Speed in miles per hour (double)
		DEBUG_PRINT(F("\nMPS = "));         DEBUG_PRINT(tinyGPS.speed.mps()); // Speed in meters per second (double)
		DEBUG_PRINT(F("\nKMPH = "));        DEBUG_PRINT(tinyGPS.speed.kmph()); // Speed in kilometers per hour (double)
	}
	if (tinyGPS.course.isUpdated()) {
		DEBUG_PRINT(F("\ncDEG = "));        DEBUG_PRINT(tinyGPS.course.value()); // Raw course in 100ths of a degree (i32)
		DEBUG_PRINT(F("\nDEG = "));         DEBUG_PRINT(tinyGPS.course.deg()); // Course in degrees (double)
	}
	if (tinyGPS.altitude.isUpdated()) {
		DEBUG_PRINT(F("\nALT KM = "));      DEBUG_PRINT(tinyGPS.altitude.kilometers()); // Altitude in kilometers (double)
		DEBUG_PRINT(F("\nALT M = "));       DEBUG_PRINT(tinyGPS.altitude.meters()); // Altitude in meters (double)
		DEBUG_PRINT(F("\nALT CM = "));      DEBUG_PRINT(tinyGPS.altitude.value()); // Raw altitude in centimeters (i32)
		DEBUG_PRINT(F("\nALT MI = "));      DEBUG_PRINT(tinyGPS.altitude.miles()); // Altitude in miles (double)
		DEBUG_PRINT(F("\nALT FT = "));      DEBUG_PRINT(tinyGPS.altitude.feet()); // Altitude in feet (double)
	}
	if (tinyGPS.satellites.isUpdated()) {
		DEBUG_PRINT(F("\nSAT = "));         DEBUG_PRINT(tinyGPS.satellites.value()); // Number of satellites in use (u32)
	}
	if (tinyGPS.hdop.isUpdated()) {
		DEBUG_PRINT(F("\nHOZ DIM = "));     DEBUG_PRINT(tinyGPS.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
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

double GPS::GetMaxAltitude() {
	return MaxAltitude;
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