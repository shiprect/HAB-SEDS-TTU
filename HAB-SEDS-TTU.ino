/**
 * @file HAB-SEDS-TTU.ino
 * 
 * The Arduino sketch.
 */
#include "Config.h"


#if PUSHBUTTON_ENABLE
	#include"src/Drivers/Pushbutton/Pushbutton.hpp"
PUSHBUTTON pushbutton;
#endif

#if PWM_ENABLE
#include"src/Drivers/PWM/PWM.hpp"
PWM pwm;
#endif

#if ANALOGPIN_ENABLE
	#include"src/Drivers/AnalogPin/AnalogPin.hpp"
ANALOGPIN analogpin;
#endif

#if BMP_ENABLE
	#include "src/Drivers/BMP/BMP.hpp"
BMP bmp;
#endif

#ifdef GPS_ENABLE

	#include "src/Drivers/GPS/GPS.hpp"


GPS gps( GPS_TX1_PIN, GPS_RX1_PIN );

GPS gps2( GPS_TX2_PIN, GPS_RX2_PIN );

#endif

#ifdef SERVO_ENABLE

	#include "src/Drivers/SERVO/Servo.hpp"


Servo CutServo;

#endif

#ifdef STATUS_ENABLE
	#include "src/Status/Status.hpp"

Status status;

#endif

#ifdef APRS_ENABLE

	#include "src/Drivers/APRS/APRS.hpp"


APRS aprs;

#endif

#ifdef SD_ENABLE

	#include "src/Drivers/SD_Card/SD_card.hpp"


SD_card sd_card;

#endif

/**
 * The initial Arduino setup function. This function will only be run once at 
 * the start of the program.
 */
void setup() {
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

	DEBUG_UART.begin( GPS_BAUDRATE );
	while ( !DEBUG_UART ) { ; // wait for serial port to connect. Needed for native USB port only
	}
	delay( 750 );

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
	CutServo.Servo_Setup();//FIXME::Naming Convention
	delay(75);
	#endif

	#if ANALOGPIN_ENABLE
	analogpin.ANALOGPIN_Setup();
	#endif

	#if PWM_ENABLE
	pwm.PWM_SETUP();
	#endif

	#if PUSHBUTTON_ENABLE
	pushbutton.PUSHBUTTON_Setup();
	#endif

	#if SD_ENABLE
	sd_card.SD_Setup();

	if(!sd_card.IsValidSD()) {
		//FIXME::Infinite while loops are a bad idea; what if this happened mid flight
		int i = 0;
		while(i > 100) {
				#if LED_ENABLE
				LED_TOGGLE(GREEN_LED);
				LED_TOGGLE(RED_LED);
				#endif
			delay(1000);
			i++;
		}
	}
	#endif

	DEBUG_PRINT( F( "Main Setup successful" ));
}


void loop() {
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
	sd_card.SD_Record(); //FIXME:: comment/uncomment
	#endif

	#if ANALOGPIN_ENABLE
	analogpin.ANALOGPIN_Update();
	#endif

	#if PWM_ENABLE
	pwm.PWM_Update();
	#endif

	#if PUSHBUTTON_ENABLE
	pushbutton.PUSHBUTTON_Update(); //TODO:: button functions should be linked to functionality, not exist as solely independent units
	#endif
}
