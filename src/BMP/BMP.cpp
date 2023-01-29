#include "BMP.hpp"


void BMP::BMP_Setup() {
	if ( !BMPModule.begin()) {
		ValidBMP = FALSE;
		DEBUG_PRINT( F( "\nBMP setup failure" ));
	}
	else {
		ValidBMP = TRUE;
		DEBUG_PRINT( F( "\nBMP setup successful" ));
	}

	sensors_event_t event;
	BMPModule.getEvent( &event );
	BaselinePressure = event.pressure;
	DEBUG_PRINT( F( "Baseline Pressure: " ));
	DEBUG_PRINT( event.pressure );
}


void BMP::BMP_Update() {
	sensors_event_t bmp_event;
	BMPModule.getEvent( &bmp_event );

	if ( bmp_event.pressure ) {
		Pressure = bmp_event.pressure;
		DEBUG_PRINT( F( "\nBMP Pressure: " ));
		DEBUG_PRINT( Pressure );
		DEBUG_PRINT( F( " hPa" ));

		/* Calculating altitude with reasonable accuracy requires pressure    *
		 * sea level pressure for your position at the moment the data is     *
		 * converted, as well as the ambient temperature in degrees           *
		 * Celsius. If you don't have these values, a 'generic' value of      *
		 * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
		 * in sensors.h), but this isn't ideal and will give variable         *
		 * results from one day to the next.                                  */

		/* First we get the current temperature from the BMP085 */
		BMPModule.getTemperature( &Temperature );
		DEBUG_PRINT( F( "\nBMP Temperature: " ));
		DEBUG_PRINT( Temperature );
		DEBUG_PRINT( F( " C" ));

		/* Then convert the atmospheric pressure, SLP and temp to altitude    */
		//float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA; //uncomment to use generic sea level value
		Altitude = BMPModule.pressureToAltitude( BaselinePressure, bmp_event.pressure, Temperature );
		if ( Altitude > MaxAltitude ) {
			MaxAltitude = Altitude;
		}
		DEBUG_PRINT( F( "\nBMP Altitude: " ));
		DEBUG_PRINT( Altitude );
		DEBUG_PRINT( F( " m" ));
		DEBUG_PRINT( F( "\nBMP MaxAltitude: " ));
		DEBUG_PRINT( MaxAltitude );
		DEBUG_PRINT( F( " m\n" ));
	}
}


bool BMP::IsValidBMP() {
	return ValidBMP;
}

float BMP::GetBaselinePressure() {
	return BaselinePressure;
}


float BMP::GetPressure() {
	return Pressure;
}


float BMP::GetTemperature() {
	return Temperature;
}


float BMP::GetAltitude() {
	return Altitude;
}


float BMP::GetMaxAltitude() {
	return MaxAltitude;
}