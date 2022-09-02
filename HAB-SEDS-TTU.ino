#include "Config.h"

#if PUSHBUTTON_ENABLE
	#include"src/Pushbutton/Pushbutton.h"
	PUSHBUTTON pushbutton;
#endif

#if PINS_ENABLE
	#include"src/Pins/Pins.hpp"
	PINS pins;
#endif

#if BMP_ENABLE
	#include "src/BMP/BMP.hpp"
	BMP bmp;
#endif

#ifdef GPS_ENABLE
	#include "src/GPS/GPS.hpp"
	GPS gps(GPS_TX1_PIN, GPS_RX1_PIN);
	GPS gps2(GPS_TX2_PIN, GPS_RX2_PIN);
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
		gps2.GPS_Setup();
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
		//DEBUG_PRINT(F("Servo Setup"));
	#endif

	#if PINS_ENABLE
		pins.PINS_Setup();
	#endif

	#if PUSHBUTTON_ENABLE
		pushbutton.PUSHBUTTON_Setup();
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
		gps2.GPS_Update();
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
		//sd_card.SD_Record(); //FIXME:: comment/uncomment
	#endif

	#if PINS_ENABLE
		pins.PINS_Update();
	#endif

	#if PUSHBUTTON_ENABLE
		pushbutton.PUSHBUTTON_Update();
		if(pushbutton.GetbuttonState() == TRUE){
			#if LED_ENABLE
				LED_ON(RED_LED);
			#endif

			int x[500];
			SoftTimer_Struct myTimer =
			{
				0, 100UL, TRUE, TRUE	// lastMillis, waitMillis, IsRepeatable, IsEnabled
			};
			int count = 0;
				//DEBUG_PRINT(F("Button Pressed 1"));
			while (count < 500) {
				if(myTimer.CheckTime() == TRUE) {
								DEBUG_PRINT(count);
					int input = pins.GetsensorValue();
					x[count] = input;
					count++;
				}
			}
				//DEBUG_PRINT(F("Button Pressed 2"));

			//sd_card.SD_arrayPass();
			#if LED_ENABLE
				LED_OFF(RED_LED);
			#endif
		}
	#endif
}