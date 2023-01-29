#ifndef __CONFIG_H__
#define __CONFIG_H__


// --------------------------------------------------------------------------
// Structure Configuration
// --------------------------------------------------------------------------
//NOTE::All macros can be overridden during compilation with gcc -DMACRONAME=value

/*Functionality Toggles*/
//NOTE::Only define one of these
#ifndef EMBEDDED__ARDUINO
	#define EMBEDDED__ARDUINO    TRUE
#endif

/* Debug Enable Toggles */
//NOTE::Only define one of these as TRUE
#ifndef DEBUG__ENABLE
	#define DEBUG__ENABLE    TRUE
#endif

/* Debug Method Toggles */
//NOTE::Only define one of these as TRUE
#ifndef DEBUG__FPRINTF
	#define DEBUG__FPRINTF    FALSE
#endif
#ifndef DEBUG__SERIAL
	#define DEBUG__SERIAL    TRUE
#endif

// --------------------------------------------------------------------------
// Board Configuration
// --------------------------------------------------------------------------
#ifndef TEENSY_ENABLE
	#define TEENSY_ENABLE    TRUE
#endif
#ifndef ESP32_ENABLE
	#define ESP32_ENABLE    FALSE
#endif
#ifndef STM32_ENABLE
	#define STM32_ENABLE    FALSE
#endif
#ifndef NANO_ENABLE
	#define NANO_ENABLE    FALSE
#endif
// --------------------------------------------------------------------------
// Module Configuration
// --------------------------------------------------------------------------
#ifndef GPS_ENABLE
	#define GPS_ENABLE FALSE
#endif
#ifndef APRS_ENABLE
	#define APRS_ENABLE FALSE   //fix compilation failing when this is commented
#endif
#ifndef BMP_ENABLE
	#define BMP_ENABLE  FALSE
#endif
#ifndef LED_ENABLE
	#define LED_ENABLE FALSE
#endif
#ifndef SD_ENABLE
	#define SD_ENABLE FALSE
#endif
#ifndef STATUS_ENABLE
	#define STATUS_ENABLE FALSE
#endif
#ifndef SERVO_ENABLE
	#define SERVO_ENABLE FALSE
#endif
#ifndef PUSHBUTTON_ENABLE
	#define PUSHBUTTON_ENABLE FALSE
#endif
#ifndef ANALOGPIN_ENABLE
	#define ANALOGPIN_ENABLE FALSE
#endif

// --------------------------------------------------------------------------
// Flight Profile
// --------------------------------------------------------------------------

#ifdef SERVO_ENABLE

const uint16_t SERVO_CUT_ALT = 28000;                      // Give desired cut altitude in meters
const uint32_t SERVO_CUT_TIMEOUT = 5400;                   // Give desired timeout in seconds
const uint8_t SERVO_START_POS = 0, SERVO_END_POS = 10;     //These three are placeholder values for now.
const uint32_t SERVO_PERIOD = 1;

#endif

// --------------------------------------------------------------------------
// Debug Functionality
// --------------------------------------------------------------------------

#define EN_PRINT_DEBUG TRUE        // General Debug

// --------------------------------------------------------------------------
// APRS config
// --------------------------------------------------------------------------

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
const char *const comment = "";

//TODO::clean up all below this line
//
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


const uint8_t GPS_VALID_POS_TIMEOUT = 50;

const uint32_t GPS_BAUDRATE = 9600;

#endif