#ifndef HAB_Teensy_hpp
#define HAB_Teensy_hpp

//#include "ProjectConfig.hpp"
//#include <stdint.h>


#if TEENSY_ENABLE
	const uint8_t RED_LED = 2;
	const uint8_t GREEN_LED = 3;
	//#define RED_LED 2
	//#define GREEN_LED 3


	const uint8_t PTT_PIN = 24;         //APRS Push to talk pin
	//const uint8_t APRS_DATA_PIN A21   // Must be A20 or A21 (Teensy 3.6)
	const uint8_t APRS_DATA_PIN = 40;   // Teensy 4.1
	//#define PTT_PIN 24
	//#define APRS_DATA_PIN 40


	const uint8_t SERVO_PIN = 6;

	const uint8_t ACCEL_SDA = 39;
	const uint8_t ACCEL_SCL = 38;

	const uint8_t GPS_TX1_PIN = 29,
				  GPS_RX1_PIN = 28,
				  GPS_TX2_PIN = 35,
				  GPS_RX2_PIN = 34;
//#endif
#endif
#endif