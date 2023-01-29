#ifndef __APRS_H__
#define __APRS_H__

#include <Arduino.h>

#include "afsk.h"
#include "ax25.h"
#include "../GPS/GPS.hpp"

#include "../../Config.h"
#include "../Status/Status.hpp"


//TODO::add this to the class
struct PathAddress {
	const char *callsign;
	uint8_t ssid;
};


//TODO::Create a robust method of message passing and transmission
class APRS {
	private:

		bool ValidAPRS;

		//TODO::Fix method of APRS period determination, config, and randomness
		uint16_t APRS_PERIOD = 300;

		void APRS_Send_with_String(
				const PathAddress *const paths, const int nPaths, const uint8_t dayOfMonth, const uint8_t hour,
				const uint8_t min, const float lat, const float lon, const float altitude, // meters
				const uint16_t heading, // degrees
				const float speed, const char symbolTableIndicator, const char symbol, const char *const comment
		);
		void logBuffer(
				const uint8_t *const buf, const int bitsSent, const uint8_t dayOfMonth, const uint8_t hour,
				const uint8_t min
		);


	public:
		APRS() {
		};

		~APRS() {
		};

		void APRS_Setup(
				const uint16_t p_preambleFlags,   // number of preambleFlags to send, must be at least 1 to frame packet
				const uint8_t pttPin,           // Use PTT pin, 0 = do not use PTT
				const uint16_t pttDelay,        // ms to wait after PTT to transmit
				const uint32_t toneLength,
				const uint32_t silenceLength    // Emit sub-audio tone before packet to trigger VOX
		);//TODO::should return true if successful, false otherwise
		void APRS_Update();//TODO::should return true if successful, false otherwise

		bool IsValidAPRS();

		void APRS_Transmit();
};

extern APRS aprs;


/*
//TODO::APRS messaging types
1 - Lat/Long Position Report Format — without Timestamp
2 - Lat/Long Position Report Format — with Timestamp
3 - Lat/Long Position Report Format — with Data Extension (no Timestamp)
4 - Lat/Long Position Report Format — with Data Extension and Timestamp
5 - Compressed Lat/Long Position Report Format — no Timestamp
6 - Compressed Lat/Long Position Report Format — with Timestamp
7 - Message Format
8 - Telemetry Report Format
9 - Maidenhead Locater Beacon
*/

/*
void APRS_Send_with_String( const PathAddress * const paths,
                const int nPaths,
                const uint8_t dayOfMonth,
                const uint8_t hour,
                const uint8_t min,
                const char* const lat_string,
                const char* const lon_string, // degrees
                const float altitude, // meters
                const uint16_t heading, // degrees
                const float speed,
                const char symbolTableIndicator,
                const char symbol,
                const char * const comment
                );



void logBuffer(const uint8_t * const buf, const int bitsSent,
    const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min);



//These functions are synchronized. They won't return until the entire packet is sent
void APRS_Send( const PathAddress * const paths,
                const int nPaths,
                const uint8_t dayOfMonth,
                const uint8_t hour,
                const uint8_t min,
                const float lat,
                const float lon, // degrees
                const float altitude, // meters
                const uint16_t heading, // degrees
                const float speed,
                const char symbolTableIndicator,
                const char symbol,
                const char * const comment
                );

void APRS_Send_modified( const PathAddress * const paths,
                const int nPaths,
                const uint8_t dayOfMonth,
                const uint8_t hour,
                const uint8_t min,
                const float lat,
                const float lon, // degrees
                const float altitude, // meters
                const uint16_t heading, // degrees
                const float speed,
                const char symbolTableIndicator,
                const char symbol,
                const char * const comment
                );



void APRS_Send_gps1( const PathAddress * const paths,
                const int nPaths,
                const uint8_t dayOfMonth,
                const uint8_t hour,
                const uint8_t min,
                const uint8_t sec,
                const float lat,
                const float lon, // degrees
                const float altitude, // meters
                const uint16_t heading, // degrees
                const float speed,
                const char symbolTableIndicator,
                const char symbol,
                const char * const comment
                );

void APRS_Send_gpsshort(const PathAddress * const paths, const int nPaths,
    const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min, const uint8_t sec,
    const float lat,
    const float lon, // degrees
    const float altitude, // meters
    const uint16_t heading, // degrees
    const float speed, const char symbolTableIndicator, const char symbol,
    const char * const comment);

void APRS_Send_gpstime(const PathAddress * const paths, const int nPaths,
    const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min, const uint8_t sec,
    const float lat,
    const float lon, // degrees
    const float altitude, // meters
    const uint16_t heading, // degrees
    const float speed, const char symbolTableIndicator, const char symbol,
    const char * const comment);
*/

#endif