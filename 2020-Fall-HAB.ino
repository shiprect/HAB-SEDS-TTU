#include "config.h"
#include "debugutils.h"
#include "hardwareutils.h"

static uint16_t APRS_PERIOD = 300;

#ifdef BMP_ENABLE
    #include "src/BMP/BMP.h"
    BMP bmp;
#endif

#ifdef GPS_ENABLE
    #include "src/GPS/GPS.h"
    GPS gps;
#endif

#ifdef SERVO_ENABLE
    #include "src/SERVO/Servo.h"
	Servo CutServo;
#endif

#ifdef STATUS_ENABLE
    #include "src/STATUS/Status.h"
	Status status;
#endif

#ifdef APRS_ENABLE
    #include "src/APRS/APRS.h"
#endif

#include "src/SD_Card/SD_card.h"
SD_card sd_card;

void setup()
{
	pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    delay(750);
    LED_ON(RED_LED);
    LED_ON(GREEN_LED);
    delay(750);
    LED_OFF(RED_LED);
    LED_OFF(GREEN_LED);
	
	
	DEBUG_UART.begin(230400);
	delay(750);
	
	#ifdef GPS_ENABLE
      delay(75);
        gps.GPS_Setup();
        delay(75);
	#endif
  
	#ifdef BMP_ENABLE
     delay(75);
		bmp.BMP_Setup();
		delay(75);
	#endif
	
	#ifdef SERVO_ENABLE
		delay(75);
		CutServo.Servo_Setup();
		delay(75);
		//DEBUG_PRINT(F("Servo Setup"));
	#endif
	
	#ifdef STATUS_ENABLE
		//#include "Status.h"
	#endif
	
	delay(750);
  
	#ifdef APRS_ENABLE
		APRS_Setup( 50,      // number of preamble flags to send
					PTT_PIN, // Use PTT pin
					100,     // ms to wait after PTT to transmit
					0, 0     // No VOX tone
		);
		delay(75);
	#endif
  
	sd_card.SD_Setup();
	
	if(!sd_card.IsValidSD()) {
		while(1) {
			LED_TOGGLE(GREEN_LED);
			LED_TOGGLE(RED_LED);
			delay(1000);
		}
	}
	DEBUG_PRINT(F("Main Setup successful"));
}


//##########################bring leather gloves####################################
// 10 meter resolution for gps, consider 100 meter resolution for when traveling
void loop()
{  
	#ifdef BMP_ENABLE 
		bmp.BMP_Update();
	#endif
	
	#ifdef GPS_ENABLE
        gps.GPS_Update(); 
	#endif
	
	#ifdef SERVO_ENABLE
		//CutServo.Servo_Status(ON);
		CutServo.Servo_Update();
		//DEBUG_PRINT(F("Servo Loop"));
	#endif
  
	#ifdef APRS_ENABLE
		if(millis() < 1000000) {
			APRS_PERIOD = 60;
		} else if(status.IsLanded()) {
			APRS_PERIOD = 300;
		}
		else {
			APRS_PERIOD = 523;
		}
		LED_ON(GREEN_LED);
		check_APRS(gps.GetAltitude(), APRS_PERIOD);
		LED_OFF(GREEN_LED);
	#else
		LED_TOGGLE(GREEN_LED);
		LED_TOGGLE(RED_LED);
	#endif
	
	#ifdef STATUS_ENABLE
		status.CheckStatus();
		status.CheckServo();
		/*if(status.IsRising()) {
			
		} else if (status.IsFalling()) {
			
		} else if(status.IsLanded()) {
			
		} else {
			
		}*/
	#endif
	
	sd_card.SD_Record();
}
