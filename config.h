#ifndef __CONFIG_H__
#define __CONFIG_H__


// --------------------------------------------------------------------------
// Hardware Configuration
// ----------------------------------------------------------------------

#define GPS_ENABLE
#define APRS_ENABLE
//#define RTTY_ENABLE
#define BMP_ENABLE
//#define ACCEL_ENABLE
#define SD_ENABLE
#define STATUS_ENABLE
#define SERVO_ENABLE

// --------------------------------------------------------------------------
// Debug Functionality
// --------------------------------------------------------------------------

//#define DEBUG               // General Debug
//#define AFSK_DEBUG          // AFSK (modulation) output
//#define APRS_DEBUG_APRS          // APRS transmit profile
//#define AX25_DEBUG          // AX.25 frame dump
//#define DEBUG_GPS_BASIC     // Basic GPS printing      
//#define GPS_ADV_DEBUG       // GPS sentence dump and checksum validation
//#define BMP_DEBUG           // BMP logging for debug
//#define RESET_DEBUG         // AVR reset
//#define RTTY_DEBUG
//#define SERVO_DEBUG	//not written yet

// --------------------------------------------------------------------------
// wiring config
// --------------------------------------------------------------------------

#define PTT_PIN 24          //APRS Push to talk pin
#define APRS_DATA_PIN A21   //DAC pin, must be A20 or A21

//#define RTTY_DATA_PIN A22
//#define RADIOEN 32

#define RED_LED 2
#define GREEN_LED 3

#define SERVO_PIN 6
#define SERVO_START_POS 0
#define SERVO_END_POS 100
#define SERVO_PERIOD 60


//#define ACCEL_SDA 39
//#define ACCEL_SCL 38


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
#define S_CALLSIGN_ID   11   // 11 is usually for balloons

// Destination callsign: APRS (with SSID=0) is usually okay.
#define D_CALLSIGN      "APRS"
#define D_CALLSIGN_ID   0

// Symbol Table: '/' is primary table '\' is secondary table
#define SYMBOL_TABLE '/' 
// Primary Table Symbols: /O=balloon, /-=House, /v=Blue Van, />=Red Car
#define SYMBOL_CHAR 'O'

// APRS comment: this goes in the comment portion of the APRS message. You
// might want to keep this short. The longer the packet, the more vulnerable
// it is to noise. 
const char * const comment = "SEDSTTU";


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
#define APRS_SLOT     0     // seconds. 0 disables slotted transmissions
//#define APRS_PERIOD 300//20//20//60    // seconds.
//uint8_t APRS_PERIOD = 300;

/*

//#define APRS_PATH_ALTITUDE   1500              // Below this altitude, ** in metres **, path will switch to WIDE1-1, WIDE2-1.  Above it will be or path or WIDE2-1 (see below)
//#define APRS_HIGH_USE_WIDE2    1                 // 1 means WIDE2-1 is used at altitude; 0 means no path is used


// Digipeating paths:
// (read more about digipeating paths here: http://wa8lmf.net/DigiPaths/ )
// The recommended digi path for a balloon is WIDE2-1 or pathless. The default
// is pathless. Uncomment the following two lines for WIDE2-1 path:
#define DIGI_PATH1      "WIDE2"
#define DIGI_PATH1_TTL  1


#define APRS_TELEM_INTERVAL  2                // How often to send telemetry packets.  Comment out to disable

#define APRS_TX_INTERVAL      1                 // APRS TX Interval in minutes
#define APRS_PRE_EMPHASIS                      // Comment out to disable 3dB pre-emphasis.
#define APRS_RANDOM          30                // Adjusts time to next transmission by up to +/1 this figure, in seconds.
                                               // So for interval of 1 (minute), and random(30), each gap could be 30 - 90 seconds.
                                               // Set to 0 to disable
*/


// --------------------------------------------------------------------------
// GPS
// --------------------------------------------------------------------------

#define GPS_VALID_POS_TIMEOUT 50

//static const uint32_t GPS_RX_PIN = 10, GPS_TX_PIN = 9;
static const uint32_t GPS_TX_PIN_TO_TEENSY = 9, GPS_RX_PIN_TO_TEENSY = 10;
static const uint32_t GPS_BAUDRATE = 9600;

// --------------------------------------------------------------------------
// RTTY
// --------------------------------------------------------------------------

//#define RTTY_BAUDRATE 4800
//#define RTTY_PERIOD   0.25    //60    // seconds.'
//#define RTTY_Channel "1b"   // values between 00 and EA, but, avoid using these extremes. hex 0-F 

//#define RTTY_PAYLOAD_ID   "CHANGE_ME"          // Do not use spaces.
//#define RTTY_FREQUENCY    434.65               // For devices that are frequency-agile
//#define RTTY_BAUD          50                  // Comment out if not using RTTY
//#define RTTY_SHIFT        425                  // Only used on boards where PWM is used for RTTY.

#endif
