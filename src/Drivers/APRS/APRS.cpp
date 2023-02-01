#include "APRS.hpp"


#define MAXSENDBUFFER 500 // Used to allocate a static buffer on the stack to build the AX25 buffer

static unsigned long transmission_timer = 0;



uint16_t preambleFlags;

////////////////////
// Convert latitude from a float to a string
void latToStr( char *const s, const int size, float lat ) {
	char hemisphere = 'N';
	if ( lat < 0 ) {
		lat = -lat;
		hemisphere = 'S';
	}
	const int deg = (int) lat;
	lat = ( lat - (float) deg ) * 60.0f;
	const int min = (int) lat;
	lat = ( lat - (float) min ) * 100.0f;
	const int minTenths = (int) ( lat + 0.5 ); // Round the tenths
	snprintf( s, size, "%02d%02d.%02d%c", deg, min, minTenths, hemisphere );
}


// Convert longitude from a float to a string
void lonToStr( char *const s, const int size, float lon ) {
	char hemisphere = 'E';
	if ( lon < 0 ) {
		lon = -lon;
		hemisphere = 'W';
	}
	const int deg = (int) lon;
	lon = ( lon - (float) deg ) * 60.0f;
	const int min = (int) lon;
	lon = ( lon - (float) min ) * 100.0f;
	const int minTenths = (int) ( lon + 0.5 ); // Round the tenths
	snprintf( s, size, "%03d%02d.%02d%c", deg, min, minTenths, hemisphere );
}
/////////////////


void APRS::APRS_Setup(
		const uint16_t p_preambleFlags,      // number of preambleFlags to send, must be at least 1 to frame packet
		const uint8_t pttPin,            // Use PTT pin, 0 = do not use PTT
		const uint16_t pttDelay,        // ms to wait after PTT to transmit
		const uint32_t toneLength, const uint32_t silenceLength    // Emit sub-audio tone before packet to trigger VOX
) {
	preambleFlags = p_preambleFlags;
	afsk_setup( pttPin, pttDelay, toneLength, silenceLength );

	// Do not start until we get a valid time reference -- for slotted transmissions.
	transmission_timer = millis() + ( 1000L * APRS_SLOT );

	ValidAPRS = TRUE;
}


void APRS::APRS_Update() {

	if ( !status.IsLaunched()) {
		APRS_PERIOD = 120;
		//} else if(status.IsLanded()) {
		//	APRS_PERIOD = 300;
	}
	else {
		APRS_PERIOD = 563;
	}

	static unsigned long MessageDelay = 0;    //takes account of delayed APRS messages due to GPS signal loss

	// Time for another APRS frame
	if (( int32_t )( millis() - transmission_timer ) >= 0 ) {
		//if (gps.ValidLocation() && (gps.AgeLocation() < (8 * GPS_VALID_POS_TIMEOUT) ) ) {
		APRS_Transmit();
		transmission_timer += (( APRS_PERIOD * 1000L ) + MessageDelay );
		MessageDelay = 0;
		DEBUG_PRINT( F( "\nAPRS message sent. GPS signal good." ));
		//} else {
		//	  DEBUG_PRINT(F("\nNo APRS message sent. GPS signal problem."));
		//}
	}
	else {
		//MessageDelay = millis();
	}


}


bool APRS::IsValidAPRS() {
	return ValidAPRS;
}

void APRS::APRS_Transmit() {
	struct PathAddress addresses[] = {{ (char *) D_CALLSIGN, D_CALLSIGN_ID },  // Destination callsign
	                                  { (char *) S_CALLSIGN, S_CALLSIGN_ID },  // Source callsign
	                                  { (char *) NULL,       0 }, // Digi1 (first digi in the chain)
	                                  { (char *) NULL,       0 }  // Digi2 (second digi in the chain)
	};


	double altitude = gps.GetAltitude();


	//	// If above 5000 feet switch to a single hop path
	int nAddresses;
	if ( altitude > 1500 ) {
		// APRS recomendations for > 5000 feet is:
		// Path: WIDE2-1 is acceptable, but no path is preferred.
		nAddresses = 3;
		addresses[ 2 ].callsign = "WIDE2";
		addresses[ 2 ].ssid = 1; //orig = 1 ===== 0-VIA;1-wide1-1;2wide2-2
	}
	else {
		// Below 1500 meters use a much more generous path (assuming a mobile station)
		// Path is "WIDE1-1,WIDE2-2"
		nAddresses = 4;
		addresses[ 2 ].callsign = "WIDE1";
		addresses[ 2 ].ssid = 1;
		addresses[ 3 ].callsign = "WIDE2";
		addresses[ 3 ].ssid = 2;
	}

	// Below 1500 meters use a much more generous path (assuming a mobile station)
	// Path is "WIDE1-1,WIDE2-2"
	//int nAddresses = 4;
	//addresses[2].callsign = "WIDE1";
	//addresses[2].ssid = 1;
	//addresses[3].callsign = "WIDE2";
	//addresses[3].ssid = 2;


	// For debugging print out the path
	//Serial.print("APRS(");
	//Serial.print(nAddresses);
	// Serial.print("): ");
	// for (int i=0; i < nAddresses; i++) {
	// Serial.print(addresses[i].callsign);
	// Serial.print('-');
	// Serial.print(addresses[i].ssid);
	// if (i < nAddresses-1) {
	// Serial.print(',');
	// }
	// }
	// Serial.print(' ');
	// Serial.print(SYMBOL_TABLE);
	// Serial.print(SYMBOL_CHAR);
	// Serial.println();

	uint8_t dayOfMonth = gps.GetDay();
	uint8_t hour = gps.GetHour();
	uint8_t min = gps.GetMinute();
	float lat = gps.GetLatitude();
	float lon = gps.GetLongitude();
	//float altitude = gps.GetAltitude();
	uint16_t heading = 00;
	float speed = gps.GetSpeed();


	//DEBUG_PRINT(gps.GetLatitude());
	//DEBUG_PRINT(gps.GetLongitude());
	//DEBUG_PRINT(gps.GetFull_Latitude());
	//DEBUG_PRINT(gps.GetFull_Longitude());

/* 	float num_whole = gps.GetLatitude();
	int intpart = (int)num_whole;
	float num_dec = gps.GetFull_Latitude();
	int decpart = int(num_dec);

	DEBUG_PRINT(intpart);
	DEBUG_PRINT(decpart);
	char lat_pos [40];
	snprintf(lat_pos, 8, "%i.%i", intpart, decpart);
	DEBUG_PRINT(F("\nAPRS Latitude: "));
	DEBUG_PRINT(lat_pos);

	num_whole = gps.GetLongitude();
	intpart = (int)num_whole;
	num_dec = gps.GetFull_Longitude();
	decpart = int(num_dec);

	DEBUG_PRINT(intpart);
	DEBUG_PRINT(decpart);
	char lon_pos [40];
	snprintf(lon_pos, 8, "%i.%i", intpart, decpart);
	DEBUG_PRINT(F("\nAPRS Longitude:"));
	DEBUG_PRINT(lon_pos); */

	//const char* const lat_string = "";
	//const char* const lon_string = "";

	// char temp[12];

	// latToStr(temp, sizeof(temp), lat);
	// ax25_send_string(temp);				// Lat:
	// const char* const lat_pos = temp;

	// lonToStr(temp, sizeof(temp), lon);
	// const char* const lon_pos = temp;

	APRS_Send_with_String( addresses, nAddresses, dayOfMonth, hour, min, lat, lon, // degrees
	                       altitude, // meters
	                       heading, speed, SYMBOL_TABLE, SYMBOL_CHAR, comment
	);


	delay( 50 );
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APRS::APRS_Send_with_String(
		const PathAddress *const paths, const int nPaths, const uint8_t dayOfMonth, const uint8_t hour,
		const uint8_t min, const float lat, const float lon, const float altitude, // meters
		const uint16_t heading, // degrees
		const float speed, const char symbolTableIndicator, const char symbol, const char *const comment
) {
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer( buf, sizeof( buf ));

	ax25_send_header( paths, nPaths, preambleFlags );

	ax25_send_byte( '/' ); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
	snprintf( temp, sizeof( temp ), "%02u%02u%02uz", (unsigned int) dayOfMonth, (unsigned int) hour,
	          (unsigned int) min
	);
	ax25_send_string( temp );

	latToStr( temp, sizeof( temp ), lat );
	ax25_send_string( temp );    //Lat:
	//snprintf(temp, sizeof(temp), "%03u", lat_string);
	//ax25_send_string(lat_string);

	ax25_send_byte( symbolTableIndicator );            // Which Symbol table to use

	lonToStr( temp, sizeof( temp ), lon );
	ax25_send_string( temp );      // Lon: 000deg and 25.80 min
	//snprintf(temp, sizeof(temp), "%03u", lon_string);
	//ax25_send_string(lon_string);	  // Lon: 000deg and 25.80 min

	ax25_send_byte( symbol );     // The symbol

	snprintf( temp, sizeof( temp ), "%03u", heading );
	ax25_send_string( temp );                // Heading (degrees)

	ax25_send_byte( '/' );                // and

	snprintf( temp, sizeof( temp ), "%03d", (unsigned int) ( speed + 0.5 ));
	ax25_send_string( temp );                // speed (knots)

	ax25_send_string( "/A=" ); // Altitude (feet). Goes anywhere in the comment area

	snprintf( temp, sizeof( temp ), "%06ld", (long) ( altitude / 0.3048 )); // 10000 ft = 3048 m
	ax25_send_string( temp );

	ax25_send_string( comment );       // Comment

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer( buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while ( afsk_busy());

	logBuffer( buf, ax25_getPacketSize(), dayOfMonth, hour, min );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Dump out the AX25 packet in a semi-readable way
// Note, the end of header and CRC are sent as ASCII characters, which they aren't
void APRS::logBuffer(
		const uint8_t *const buf, const int bitsSent, const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min
) {
	//Serial.printf("Bits in packet %d: ", bitsSent);
	// #TODO::FIXME
	Serial.print( dayOfMonth );
	Serial.print( ',' );
	Serial.print( hour );
	Serial.print( ',' );
	Serial.print( min );
	Serial.print( ',' );

	uint8_t frameState = 0; // 0-No start, 1-start, 2-in header, 3-In info
	uint8_t bSoFar = 0x00;
	uint8_t gotBit = 0;
	int numOnes = 0;
	for ( int onBit = 0; onBit < bitsSent; onBit++ ) {
		uint8_t bit = buf[ onBit >> 3 ] & ( 1 << ( onBit & 7 ));
		if ( numOnes == 5 ) {
			// This may be a 0 due to bit stuffing
			if ( bit ) { // Maybe it's a 0x7e
				onBit++;
				bit = buf[ onBit >> 3 ] & ( 1 << ( onBit & 7 ));
				if ( gotBit == 6 && bSoFar == 0x3e && !bit ) {
					// Got 0x7e frame start/end
					if ( frameState == 0 ) {
						frameState = 1;
						Serial.print( '[' );
					}
					else if ( frameState == 3 || frameState == 2 ) {
						frameState = 0;
						Serial.print( ']' );
					}
					bSoFar = 0x00;
					gotBit = 0;
				}
				else {
					Serial.print( 'X' ); // Error
				}
			}
			numOnes = 0;
			continue;
		}
		if ( bit ) {
			// Set the one bit
			bSoFar |= ( 1 << gotBit );
			numOnes++;
		}
		else {
			numOnes = 0;
		}
		gotBit++;
		if ( gotBit == 8 ) {
			// Got a byte;
			if ( frameState == 1 ) {
				frameState = 2;
			}
			else if ( frameState == 2 && bSoFar == 0xf0 ) { // 0xf0 is the last byte of the header
				frameState = 3;
			}
			if ( frameState == 2 ) {
				// In header
				Serial.print((char) ( bSoFar >> 1 ));
			}
			else {
				// In info
				Serial.print((char) bSoFar );
			}
			bSoFar = 0x00;
			gotBit = 0;
		}
	}
	Serial.println();
}















/*

uint16_t preambleFlags;


void check_APRS(float altitude, uint16_t APRS_PERIOD) {
	static unsigned long MessageDelay = 0;	//takes account of delayed APRS messages due to GPS signal loss

	// Time for another APRS frame
	if ((int32_t) (millis() - transmission_timer) >= 0) {
		//if (gps.ValidLocation() && (gps.AgeLocation() < (8 * GPS_VALID_POS_TIMEOUT) ) ) {
			send_APRS(altitude);
			transmission_timer += ( (APRS_PERIOD * 1000L) + MessageDelay);
			MessageDelay = 0;
			DEBUG_PRINT(F("\nAPRS message sent. GPS signal good."));
		//} else {
		//	  DEBUG_PRINT(F("\nNo APRS message sent. GPS signal problem."));
		//}
	} else {
		//MessageDelay = millis();
	}
}


// Function to broadcast your location
void test_broadcastLocation(float altitude) {
	struct PathAddress addresses[] = {
		{(char *)D_CALLSIGN, D_CALLSIGN_ID},  // Destination callsign
		{(char *)S_CALLSIGN, S_CALLSIGN_ID},  // Source callsign
		{(char *)NULL, 0}, // Digi1 (first digi in the chain)
		{(char *)NULL, 0}  // Digi2 (second digi in the chain)
	};
	//	// If above 5000 feet switch to a single hop path
	  int nAddresses;
	  if (altitude > 1500) {
		// APRS recomendations for > 5000 feet is:
		// Path: WIDE2-1 is acceptable, but no path is preferred.
		nAddresses = 3;
		addresses[2].callsign = "WIDE2";
		addresses[2].ssid = 1; //orig = 1 ===== 0-VIA;1-wide1-1;2wide2-2
	  } else {
		// Below 1500 meters use a much more generous path (assuming a mobile station)
		// Path is "WIDE1-1,WIDE2-2"
		nAddresses = 4;
		addresses[2].callsign = "WIDE1";
		addresses[2].ssid = 1;
		addresses[3].callsign = "WIDE2";
		addresses[3].ssid = 2;
	  }

	// Below 1500 meters use a much more generous path (assuming a mobile station)
	// Path is "WIDE1-1,WIDE2-2"
	//int nAddresses = 4;
	//addresses[2].callsign = "WIDE1";
	//addresses[2].ssid = 1;
	//addresses[3].callsign = "WIDE2";
	//addresses[3].ssid = 2;


	// For debugging print out the path
	//Serial.print("APRS(");
	//Serial.print(nAddresses);
	// Serial.print("): ");
	// for (int i=0; i < nAddresses; i++) {
		// Serial.print(addresses[i].callsign);
		// Serial.print('-');
		// Serial.print(addresses[i].ssid);
		// if (i < nAddresses-1) {
			// Serial.print(',');
		// }
	// }
	// Serial.print(' ');
	// Serial.print(SYMBOL_TABLE);
	// Serial.print(SYMBOL_CHAR);
	// Serial.println();

	uint8_t dayOfMonth = gps.GetDay();
	uint8_t hour = gps.GetHour();
	uint8_t min = gps.GetMinute();
	uint8_t sec = gps.GetSecond();
	float lat = gps.GetFull_Latitude();
	float lon = gps.GetFull_Longitude();
	//float altitude = gps.GetAltitude();
	uint16_t heading = 00;
	float speed = gps.GetSpeed();


	DEBUG_PRINT(gps.GetLatitude());
	DEBUG_PRINT(gps.GetLongitude());
	DEBUG_PRINT(gps.GetFull_Latitude());
	DEBUG_PRINT(gps.GetFull_Longitude());

	float num_whole = gps.GetLatitude();
	int intpart = (int)num_whole;
	float num_dec = gps.GetFull_Latitude();
	int decpart = int(num_dec);

	//DEBUG_PRINT(intpart);
	//DEBUG_PRINT(decpart);
	char lat_pos [40];
	snprintf(lat_pos, 8, "%i.%i", intpart, decpart);
	DEBUG_PRINT(F("\nAPRS Latitude: "));
	DEBUG_PRINT(lat_pos);

	num_whole = gps.GetLongitude();
	intpart = (int)num_whole;
	num_dec = gps.GetFull_Longitude();
	decpart = int(num_dec);

	//DEBUG_PRINT(intpart);
	//DEBUG_PRINT(decpart);
	char lon_pos [40];
	snprintf(lon_pos, 8, "%i.%i", intpart, decpart);
	DEBUG_PRINT(F("\nAPRS Longitude:"));
	DEBUG_PRINT(lon_pos);

	const char* const lat_string = "";
	const char* const lon_string = "";


	APRS_Send_with_String(addresses,
			  nAddresses,
			  dayOfMonth,
			  hour,
			  min,
			  lat_pos,
			  lon_pos, // degrees
			  altitude, // meters
			  heading,
			  speed,
			  SYMBOL_TABLE,
			  SYMBOL_CHAR,
			  comment);


	delay(50);

//	// Send the packet
//	APRS_Send(addresses, nAddresses
//		,gps.day, gps.hour, gps.minute
//		,gps.latitude, gps.longitude // degrees
//		,gps.altitude // meters
//		,gps.heading
//		,gps.speed
//		,SYMBOL_TABLE
//		,SYMBOL_CHAR
//		,comment);
}


void APRS_Send_with_String(const PathAddress * const paths, const int nPaths,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min,
	const char* const lat_string,
	const char* const lon_string, // degrees
	const float altitude, // meters
	const uint16_t heading, // degrees
	const float speed, const char symbolTableIndicator, const char symbol,
	const char * const comment)
{
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer(buf, sizeof(buf));

	ax25_send_header(paths, nPaths, preambleFlags);

	ax25_send_byte('/'); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
	snprintf(temp, sizeof(temp), "%02u%02u%02uz", (unsigned int) dayOfMonth,
												  (unsigned int) hour,
												  (unsigned int) min);
	ax25_send_string(temp);

	//latToStr(temp, sizeof(temp), lat);
	//ax25_send_string(temp);	//Lat:
	//snprintf(temp, sizeof(temp), "%03u", lat_string);
	ax25_send_string(lat_string);

	ax25_send_byte(symbolTableIndicator);			// Which Symbol table to use

	//lonToStr(temp, sizeof(temp), lon);
	//ax25_send_string(temp);	  // Lon: 000deg and 25.80 min
	//snprintf(temp, sizeof(temp), "%03u", lon_string);
	ax25_send_string(lon_string);	  // Lon: 000deg and 25.80 min

	ax25_send_byte(symbol);	 // The symbol

	snprintf(temp, sizeof(temp), "%03u", heading);
	ax25_send_string(temp);				// Heading (degrees)

	ax25_send_byte('/');				// and

	snprintf(temp, sizeof(temp), "%03d", (unsigned int) (speed + 0.5));
	ax25_send_string(temp);				// speed (knots)

	ax25_send_string("/A="); // Altitude (feet). Goes anywhere in the comment area

	snprintf(temp, sizeof(temp), "%06ld", (long) (altitude / 0.3048)); // 10000 ft = 3048 m
	ax25_send_string(temp);

	ax25_send_string(comment);	   // Comment

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer(buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while (afsk_busy())
	;

	logBuffer(buf, ax25_getPacketSize(), dayOfMonth, hour, min);
}




char *ax25_base91enc(char *s, uint8_t n, uint32_t v)
{
	// Creates a Base-91 representation of the value in v in the string
	// pointed to by s, n-characters long. String length should be n+1.
	for(s += n, *s = '\0'; n; n--) {
		*(--s) = v % 91 + 33;
		v /= 91;
	}

		return(s);
}

// Convert latitude from a float to a string
void latToStr(char * const s, const int size, float lat)
{
	char hemisphere = 'N';
	if (lat < 0) {
		lat = -lat;
		hemisphere = 'S';
	}
	const int deg = (int) lat;
	lat = (lat - (float) deg) * 60.0f;
	const int min = (int) lat;
	lat = (lat - (float) min) * 100.0f;
	const int minTenths = (int) (lat + 0.5); // Round the tenths
	snprintf(s, size, "%02d%02d.%02d%c", deg, min, minTenths, hemisphere);
}


// Convert longitude from a float to a string
void lonToStr(char * const s, const int size, float lon)
{
	char hemisphere = 'E';
	if (lon < 0) {
		lon = -lon;
		hemisphere = 'W';
	}
	const int deg = (int) lon;
	lon = (lon - (float) deg) * 60.0f;
	const int min = (int) lon;
	lon = (lon - (float) min) * 100.0f;
	const int minTenths = (int) (lon + 0.5); // Round the tenths
	snprintf(s, size, "%03d%02d.%02d%c", deg, min, minTenths, hemisphere);
}


// Dump out the AX25 packet in a semi-readable way
// Note, the end of header and CRC are sent as ASCII characters, which they aren't
void logBuffer(const uint8_t * const buf, const int bitsSent,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min)
	{
	Serial.printf("Bits in packet %d: ", bitsSent);
	Serial.print(dayOfMonth);
	Serial.print(',');
	Serial.print(hour);
	Serial.print(',');
	Serial.print(min);
	Serial.print(',');

	uint8_t frameState = 0; // 0-No start, 1-start, 2-in header, 3-In info
	uint8_t bSoFar = 0x00;
	uint8_t gotBit = 0;
	int numOnes = 0;
	for (int onBit = 0; onBit < bitsSent; onBit++) {
		uint8_t bit = buf[onBit >> 3] & (1 << (onBit & 7));
		if (numOnes == 5) {
			// This may be a 0 due to bit stuffing
			if (bit) { // Maybe it's a 0x7e
				onBit++;
				bit = buf[onBit >> 3] & (1 << (onBit & 7));
				if (gotBit == 6 && bSoFar == 0x3e && !bit) {
					// Got 0x7e frame start/end
					if (frameState == 0) {
						frameState = 1;
						Serial.print('[');
					} else
						if (frameState == 3 || frameState == 2) {
							frameState = 0;
							Serial.print(']');
						}
						bSoFar = 0x00;
						gotBit = 0;
					} else {
						Serial.print('X'); // Error
					}
			}
		numOnes = 0;
		continue;
		}
		if (bit) {
			// Set the one bit
			bSoFar |= (1 << gotBit);
			numOnes++;
		} else {
			numOnes = 0;
		}
		gotBit++;
		if (gotBit == 8) {
			// Got a byte;
			if (frameState == 1) {
				frameState = 2;
			} else
				if (frameState == 2 && bSoFar == 0xf0) { // 0xf0 is the last byte of the header
					frameState = 3;
				}
			if (frameState == 2) {
				// In header
				Serial.print((char) (bSoFar >> 1));
			} else {
				// In info
				Serial.print((char) bSoFar);
			}
			bSoFar = 0x00;
			gotBit = 0;
		}
	}
	Serial.println();
}


void APRS_Setup(const uint16_t p_preambleFlags, const uint8_t pttPin,		   \
				const uint16_t pttDelay, const uint32_t toneLength,			   \
				const uint32_t silenceLength) {

	preambleFlags = p_preambleFlags;
	afsk_setup(pttPin, pttDelay, toneLength, silenceLength);

	// Do not start until we get a valid time reference -- for slotted transmissions.
	transmission_timer = millis() + (1000L * APRS_SLOT);
}


// This can operate in two modes, PTT or VOX
// In VOX mode send a toneLength and silenceLength. The audible tone will be sent for that
// many milliseconds to open up VOX, and then that many MS of silence, then the packet will
// begin.
// In PTT mode the pin given will be raised high, and then PTT_DELAY ms later, the packet will
// begin
void APRS_Send(const PathAddress * const paths, const int nPaths,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min,
	const float lat,
	const float lon, // degrees
	const float altitude, // meters
	const uint16_t heading, // degrees
	const float speed, const char symbolTableIndicator, const char symbol,
	const char * const comment)
{
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer(buf, sizeof(buf));

	ax25_send_header(paths, nPaths, preambleFlags);

	ax25_send_byte('/'); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
	snprintf(temp, sizeof(temp), "%02u%02u%02uz", (unsigned int) dayOfMonth,
												  (unsigned int) hour,
												  (unsigned int) min);
	ax25_send_string(temp);

	latToStr(temp, sizeof(temp), lat);
	ax25_send_string(temp);				// Lat:

	ax25_send_byte(symbolTableIndicator);			// Which Symbol table to use

	lonToStr(temp, sizeof(temp), lon);
	ax25_send_string(temp);		// Lon: 000deg and 25.80 min

	ax25_send_byte(symbol);	 // The symbol

	snprintf(temp, sizeof(temp), "%03u", heading);
	ax25_send_string(temp);				// Heading (degrees)

	ax25_send_byte('/');				// and

	snprintf(temp, sizeof(temp), "%03d", (unsigned int) (speed + 0.5));
	ax25_send_string(temp);				// speed (knots)

	ax25_send_string("/A="); // Altitude (feet). Goes anywhere in the comment area

	snprintf(temp, sizeof(temp), "%06ld", (long) (altitude / 0.3048)); // 10000 ft = 3048 m
	ax25_send_string(temp);

	ax25_send_string(comment);	   // Comment

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer(buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while (afsk_busy())
		;

	logBuffer(buf, ax25_getPacketSize(), dayOfMonth, hour, min);
}


void APRS_Send_modified(const PathAddress * const paths, const int nPaths,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min,
	const float lat,
	const float lon, // degrees
	const float altitude, // meters
	const uint16_t heading, // degrees
	const float speed, const char symbolTableIndicator, const char symbol,
	const char * const comment)
{
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer(buf, sizeof(buf));

	ax25_send_header(paths, nPaths, preambleFlags);

	ax25_send_byte('/'); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
	snprintf(temp, sizeof(temp), "%02u%02u%02uz", (unsigned int) dayOfMonth,
												  (unsigned int) hour,
												  (unsigned int) min);
	ax25_send_string(temp);

	latToStr(temp, sizeof(temp), lat);
	ax25_send_string(temp);				// Lat:

	ax25_send_byte(symbolTableIndicator);			// Which Symbol table to use

	lonToStr(temp, sizeof(temp), lon);
	ax25_send_string(temp);		// Lon: 000deg and 25.80 min

	ax25_send_byte(symbol);	 // The symbol

	snprintf(temp, sizeof(temp), "%03u", heading);
	ax25_send_string(temp);				// Heading (degrees)

	ax25_send_byte('/');				// and

	snprintf(temp, sizeof(temp), "%03d", (unsigned int) (speed + 0.5));
	ax25_send_string(temp);				// speed (knots)

	ax25_send_string("/A="); // Altitude (feet). Goes anywhere in the comment area

	snprintf(temp, sizeof(temp), "%06ld", (long) (altitude / 0.3048)); // 10000 ft = 3048 m
	ax25_send_string(temp);

	ax25_send_string(comment);	   // Comment

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer(buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while (afsk_busy())
		;

	logBuffer(buf, ax25_getPacketSize(), dayOfMonth, hour, min);
}
*/



////Exported functions
// void APRS_Send()
// {
// char temp[12];					  // Temperature (int/ext)
// const struct s_address addresses[] = {
// {D_CALLSIGN, D_CALLSIGN_ID},	 // Destination callsign
// {S_CALLSIGN, S_CALLSIGN_ID},	 // Source callsign (-11 = balloon, -9 = car)
// #ifdef DIGI_PATH1
// {DIGI_PATH1, DIGI_PATH1_TTL}, // Digi1 (first digi in the chain)
// #endif
// #ifdef DIGI_PATH2
// {DIGI_PATH2, DIGI_PATH2_TTL}, // Digi2 (second digi in the chain)
// #endif
// };

// ax25_send_header(addresses, sizeof(addresses)/sizeof(s_address));
// ax25_send_byte('/');				 // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
////ax25_send_string("021709z");	   // 021709z = 2nd day of the month, 17:09 zulu (UTC/GMT)
// ax25_send_string(gps_time);		 // 170915 = 17h:09m:15s zulu (not allowed in Status Reports)
// ax25_send_byte('h');
// ax25_send_string(gps_aprs_lat);	 // Lat: 38deg and 22.20 min (.20 are NOT seconds, but 1/100th of minutes)
// ax25_send_byte('/');				 // Symbol table
// ax25_send_string(gps_aprs_lon);	 // Lon: 000deg and 25.80 min
// ax25_send_byte('O');				 // Symbol: O=balloon, -=QTH
// snprintf(temp, 4, "%03d", (int)(gps_course + 0.5));
// ax25_send_string(temp);			 // Course (degrees)
// ax25_send_byte('/');				 // and
// snprintf(temp, 4, "%03d", (int)(gps_speed + 0.5));
// ax25_send_string(temp);			 // speed (knots)
// ax25_send_string("/A=");			 // Altitude (feet). Goes anywhere in the comment area
// snprintf(temp, 7, "%06ld", (long)(meters_to_feet(gps_altitude) + 0.5));
// ax25_send_string(temp);
// ax25_send_string("/Ti=");
// snprintf(temp, 6, "%d", sensors_int_lm60());
// ax25_send_string(temp);
// ax25_send_string("/Te=");
// snprintf(temp, 6, "%d", sensors_ext_lm60());
// ax25_send_string(temp);
// ax25_send_string("/V=");
// snprintf(temp, 6, "%d", sensors_vin());
// ax25_send_string(temp);
// ax25_send_byte(' ');
// ax25_send_string(APRS_COMMENT);	 // Comment
// ax25_send_footer();

// ax25_flush_frame();				 // Tell the modem to go
// }

/*
void APRS_Send_gps1(const PathAddress * const paths, const int nPaths,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min, const uint8_t sec,
	const float lat,
	const float lon, // degrees
	const float altitude, // meters
	const uint16_t heading, // degrees
	const float speed, const char symbolTableIndicator, const char symbol,
	const char * const comment)
{
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer(buf, sizeof(buf));

	ax25_send_header(paths, nPaths, preambleFlags);

	ax25_send_byte('!'); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data

	latToStr(temp, sizeof(temp), lat);
	ax25_send_string(temp);				// Lat:

	ax25_send_byte(symbolTableIndicator);			// Which Symbol table to use

	lonToStr(temp, sizeof(temp), lon);
	ax25_send_string(temp);		// Lon: 000deg and 25.80 min

	ax25_send_byte(symbol);	 // The symbol

	ax25_send_string(comment);	   // Comment

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer(buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while (afsk_busy())
		;

	logBuffer(buf, ax25_getPacketSize(), dayOfMonth, hour, min);
}

void APRS_Send_gpsshort(const PathAddress * const paths, const int nPaths,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min, const uint8_t sec,
	const float lat,
	const float lon, // degrees
	const float altitude, // meters
	const uint16_t heading, // degrees
	const float speed, const char symbolTableIndicator, const char symbol,
	const char * const comment)
{
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer(buf, sizeof(buf));

	ax25_send_header(paths, nPaths, preambleFlags);

	ax25_send_byte('!'); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data

	latToStr(temp, sizeof(temp), lat);
	ax25_send_string(temp);				// Lat:

	ax25_send_byte(symbolTableIndicator);			// Which Symbol table to use

	lonToStr(temp, sizeof(temp), lon);
	ax25_send_string(temp);		// Lon: 000deg and 25.80 min

	ax25_send_byte(symbol);	 // The symbol

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer(buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while (afsk_busy())
		;

	logBuffer(buf, ax25_getPacketSize(), dayOfMonth, hour, min);
}


void APRS_Send_gpstime(const PathAddress * const paths, const int nPaths,
	const uint8_t dayOfMonth, const uint8_t hour, const uint8_t min, const uint8_t sec,
	const float lat,
	const float lon, // degrees
	const float altitude, // meters
	const uint16_t heading, // degrees
	const float speed, const char symbolTableIndicator, const char symbol,
	const char * const comment)
{
	uint8_t buf[MAXSENDBUFFER];
	char temp[12];

	ax25_initBuffer(buf, sizeof(buf));

	ax25_send_header(paths, nPaths, preambleFlags);

	ax25_send_byte('/'); // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
	snprintf(temp, sizeof(temp), "%02u%02u%02uh", (unsigned int) hour,
												  (unsigned int) min,
												  (unsigned int) sec);
	ax25_send_string(temp);

	latToStr(temp, sizeof(temp), lat);
	ax25_send_string(temp);				// Lat:

	ax25_send_byte(symbolTableIndicator);			// Which Symbol table to use

	lonToStr(temp, sizeof(temp), lon);
	ax25_send_string(temp);		// Lon: 000deg and 25.80 min

	ax25_send_byte(symbol);	 // The symbol

	ax25_send_footer();

	Serial.flush(); // Make sure all Serial data (which is based on interrupts) is done before you start sending.

	// Set the buffer of bits we are going to send
	afsk_set_buffer(buf, ax25_getPacketSize());

	Serial.flush(); // Wait until all characters are sent

	// OK, no more operations until this is done.
	afsk_start();
	while (afsk_busy()) {
	}

	logBuffer(buf, ax25_getPacketSize(), dayOfMonth, hour, min);
}
*/