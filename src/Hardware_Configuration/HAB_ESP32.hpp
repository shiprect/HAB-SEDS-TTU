#ifndef HAB_ESP32_hpp
#define HAB_ESP32_hpp

#if ESP32_ENABLE

	const uint8_t RED_LED = 2;
	const uint8_t GREEN_LED = 3;

	const uint8_t PTT_PIN = 24;         //APRS Push to talk pin
	//#define APRS_DATA_PIN A21         //DAC pin, must be A20 or A21 (Teensy 3.6)
	const uint8_t APRS_DATA_PIN = 40;   // Teensy 4.1

	//#define RTTY_DATA_PIN A22         // Teensy 3.6
	const uint8_t RTTY_DATA_PIN = 41;   // Teensy 4.1
	const uint8_t RADIOEN = 32;

	const uint8_t SERVO_PIN = 6;

	const uint8_t ACCEL_SDA = 39;
	const uint8_t ACCEL_SCL = 38;

	const uint32_t GPS_TX_PIN_TO_TEENSY = 29,
				   GPS_RX_PIN_TO_TEENSY = 28;

#endif

#endif