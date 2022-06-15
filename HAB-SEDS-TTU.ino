#include "Config.h"

#if BMP_ENABLE
	#include "src/BMP/BMP.hpp"
	BMP bmp;
#endif

#ifdef GPS_ENABLE
	#include "src/GPS/GPS.hpp"
	GPS gps;
#endif

#ifdef SERVO_ENABLE
	#include "src/SERVO/Servo.hpp"
	Servo CutServo;
#endif

#ifdef STATUS_ENABLE
	#include "src/Status/Status.hpp"
	Status status;
#endif

#ifdef APRS_ENABLE
	#include "src/APRS/APRS.hpp"
	APRS aprs;
#endif

#ifdef SD_ENABLE
	#include "src/SD_Card/SD_card.hpp"
	SD_card sd_card;
#endif

void setup()
{
	#if LED_ENABLE
		pinMode(RED_LED, OUTPUT);
		pinMode(GREEN_LED, OUTPUT);
		delay(750);
		LED_ON(RED_LED);
		LED_ON(GREEN_LED);
		delay(750);
		LED_OFF(RED_LED);
		LED_OFF(GREEN_LED);
	#endif

	DEBUG_UART.begin(9600); //FIXME::Remove this magic number and put it in config //Other baud rates not supported by macs???(Chris)
    while (!DEBUG_UART) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
	delay(750);

	#if GPS_ENABLE
		delay(75);
		gps.GPS_Setup();
		delay(75);
	#endif

	#if BMP_ENABLE
		delay(75);
		bmp.BMP_Setup();
		delay(75);
	#endif

	#if SERVO_ENABLE
		delay(75);
		CutServo.Servo_Setup();
		delay(75);
		//DEBUG_PRINT(F("Servo Setup"));
	#endif

	#if STATUS_ENABLE

	#endif

	delay(750);

	#if APRS_ENABLE
		aprs.APRS_Setup( 50,	  // number of preamble flags to send
					PTT_PIN, // Use PTT pin
					100,	 // ms to wait after PTT to transmit
					0, 0	 // No VOX tone
		);
		delay(75);
	#endif

	#if SD_ENABLE
		sd_card.SD_Setup();

		if(!sd_card.IsValidSD()) {
            //FIXME::Infinite while loops are a bad idea; what if this happened mid flight
			while(1) {
				#if LED_ENABLE
					LED_TOGGLE(GREEN_LED);
					LED_TOGGLE(RED_LED);
				#endif
				delay(1000);
			}
		}
	#endif

	DEBUG_PRINT(F("Main Setup successful"));
}


void loop()
{
	#if BMP_ENABLE
		bmp.BMP_Update();
	#endif

	#if GPS_ENABLE
		gps.GPS_Update();
	#endif

	#if SERVO_ENABLE
		CutServo.Servo_Update();
	#endif

	#if APRS_ENABLE
		aprs.APRS_Update();
	#endif

	#if STATUS_ENABLE
		status.CheckStatus();
		status.CheckServo(); //FIXME::This shouldn't be here
	#endif

	#if SD_ENABLE
		sd_card.SD_Record();
	#endif
}