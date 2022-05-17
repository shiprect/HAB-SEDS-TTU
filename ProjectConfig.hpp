#ifndef __CONFIG_H__
#define __CONFIG_H__



// --------------------------------------------------------------------------
// Module Configuration
// --------------------------------------------------------------------------

#define GPS_ENABLE
//#define APRS_ENABLE	//fix compilation failing when this is commented
//#define BMP_ENABLE
#define LED_ENABLE
//#define ACCEL_ENABLE
//#define SD_ENABLE
//#define STATUS_ENABLE
//#define SERVO_ENABLE
//#define RTTY_ENABLE
#define TEENSY_ENABLE
//#define ESP32_ENABLE
//#define STM32_ENABLE

#include "HAB_Teensy.hpp"
//#include "HAB_STM32.hpp"
//#include "HAB_ESP32.hpp"

// --------------------------------------------------------------------------
// Flight Profile
// ----------------------------------------------------------------------

//#ifdef SERVO_ENABLE
	const uint16_t SERVO_CUT_ALT = 28000;						// Give desired cut altitude in meters
	const uint32_t SERVO_CUT_TIMEOUT = 5400;					// Give desired timeout in seconds
  const uint8_t SERVO_START_POS = 0,          //These three are placeholder values for now.
                SERVO_END_POS = 10,
                SERVO_PERIOD = 1;
//#endif

// --------------------------------------------------------------------------
// Debug Functionality
// --------------------------------------------------------------------------

#define DEBUG               // General Debug
//#define AFSK_DEBUG          // AFSK (modulation) output
//#define APRS_DEBUG_APRS          // APRS transmit profile
//#define AX25_DEBUG          // AX.25 frame dump
//#define DEBUG_GPS_BASIC     // Basic GPS printing      
//#define GPS_ADV_DEBUG       // GPS sentence dump and checksum validation
//#define BMP_DEBUG           // BMP logging for debug
//#define RESET_DEBUG         // AVR reset
//#define RTTY_DEBUG	//not written yet
//#define SERVO_DEBUG	//not written yet


// --------------------------------------------------------------------------
// 
// --------------------------------------------------------------------------

















// --------------------------------------------------------------------------
// APRS config
// --------------------------------------------------------------------------

//#ifdef APRS_ENABLE
	//static uint16_t APRS_PERIOD = 300;	///fix this

	// Set your callsign and SSID here. Common values for the SSID are
	// (from http://zlhams.wikidot.com/aprs-ssidguide):
	//
	// - Balloons:  11
	// - Cars:       9
	// - Home:       0
	// - IGate:      5
	#define S_CALLSIGN      "KN4JLK"
	const uint8_t S_CALLSIGN_ID = 11;   // 11 is usually for balloons

	// Destination callsign: APRS (with SSID=0) is usually okay.
	#define D_CALLSIGN      "APRS"
	const uint8_t D_CALLSIGN_ID = 0;

	// Symbol Table: '/' is primary table '\' is secondary table
	#define SYMBOL_TABLE '/' 
	// Primary Table Symbols: /O=balloon, /-=House, /v=Blue Van, />=Red Car
	#define SYMBOL_CHAR 'O'

	// APRS comment: this goes in the comment portion of the APRS message. You
	// might want to keep this short. The longer the packet, the more vulnerable
	// it is to noise. 
	const char * const comment = "";//"SEDSTTU";


	// APRS packets are slotted so that multiple trackers can be used without
	// them stepping on one another. The transmission times are governed by
	// the formula:
	//
	//         APRS_SLOT (seconds) + n * APRS_PERIOD (seconds)
	//
	// When launching multiple balloons, use the same APRS_PERIOD in all balloons
	// and set APRS_SLOT so that the packets are spaced equally in time.
	// Eg. for two balloons and APRS_PERIOD = 60, set APRS_SLOT to 0 and 30, 
	// respectively. The first balloon will transmit at 00:00:00, 00:01:00, 
	// 00:02:00, etc. and the second balloon will transmit at 00:00:30, 00:01:30,
	// 00:02:30, etc.
	const uint8_t APRS_SLOT = 0;    // seconds. 0 disables slotted transmissions
	//#define APRS_PERIOD 300//20//20//60    // seconds.
	//uint8_t APRS_PERIOD = 300;

	/*

	//const uint8_t APRS_PATH_ALTITUDE = 1500;	// Below this altitude, ** in metres **, path will switch to WIDE1-1, WIDE2-1.  Above it will be or path or WIDE2-1 (see below)
	//const uint8_t APRS_HIGH_USE_WIDE2 = 1;        // 1 means WIDE2-1 is used at altitude; 0 means no path is used


	// Digipeating paths:
	// (read more about digipeating paths here: http://wa8lmf.net/DigiPaths/ )
	// The recommended digi path for a balloon is WIDE2-1 or pathless. The default
	// is pathless. Uncomment the following two lines for WIDE2-1 path:
	#define DIGI_PATH1      "WIDE2"
	coust uint8_t DIGI_PATH1_TTL = 1;


	const uint8_t APRS_TELEM_INTERVAL = 2;                // How often to send telemetry packets.  Comment out to disable

	const uint8_t APRS_TX_INTERVAL = 1;                 // APRS TX Interval in minutes
	#define APRS_PRE_EMPHASIS                      // Comment out to disable 3dB pre-emphasis.
	const uint8_t APRS_RANDOM = 30;                // Adjusts time to next transmission by up to +/1 this figure, in seconds.
						       // So for interval of 1 (minute), and random(30), each gap could be 30 - 90 seconds.
						       // Set to 0 to disable
	*/
//#endif


// --------------------------------------------------------------------------
// GPS
// --------------------------------------------------------------------------

#ifdef GPS_ENABLE
	const uint8_t GPS_VALID_POS_TIMEOUT = 50;
	static const uint32_t GPS_BAUDRATE = 9600;
#endif

// --------------------------------------------------------------------------
// RTTY
// --------------------------------------------------------------------------

#ifdef RTTY_ENABLE
	//const uint8_t RTTY_BAUDRATE = 4800;
	//const uint8_t RTTY_PERIOD = 0.25;    //60    // seconds.'
	//#define RTTY_Channel "1b"   // values between 00 and EA, but, avoid using these extremes. hex 0-F 

	//#define RTTY_PAYLOAD_ID   "CHANGE_ME"			// Do not use spaces.
	//const uint8_t RTTY_FREQUENCY = 434.65;		// For devices that are frequency-agile
	//const uint8_t RTTY_BAUD = 50;				// Comment out if not using RTTY
	//const uint8_t RTTY_SHIFT = 425;			// Only used on boards where PWM is used for RTTY.
#endif

#endif
