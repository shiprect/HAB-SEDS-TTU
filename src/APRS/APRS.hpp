#ifndef __APRS_H__
#define __APRS_H__

#include <Arduino.h>

#include "afsk.h"
#include "ax25.h"
#include "../GPS/GPS.hpp"

#include "../../config.h"
#include "../utilities/utilities.h"


#define MAXSENDBUFFER 500 // Used to allocate a static buffer on the stack to build the AX25 buffer

static unsigned long transmission_timer = 0;


struct PathAddress
{
    const char *callsign;
    uint8_t ssid;
};


void APRS_Setup(const uint16_t preambleFlags,   // number of preambleFlags to send, must be at least 1 to frame packet
                const uint8_t pttPin,           // Use PTT pin, 0 = do not use PTT
                const uint16_t pttDelay,        // ms to wait after PTT to transmit
                const uint32_t toneLength,
                const uint32_t silenceLength    // Emit sub-audio tone before packet to trigger VOX
                );

void send_APRS(float altitude);

void check_APRS(float altitude, uint16_t APRS_PERIOD);

void test_broadcastLocation(float altitude);
                
/*
TODO: APRS messaging types
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


#endif
