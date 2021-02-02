#include "Servo.h"


void Servo::Servo_Setup(){
    ServoPWM.attach(SERVO_PIN);
}


void Servo::Servo_Status(bool Status) {
	ServoStatus = Status;
}


void Servo::Servo_Move(uint8_t Position) {
	ServoPWM.write(Position);
}


void Servo::Servo_Update() {
	if(ServoStatus == ON) {
		static unsigned long servo_timer = 0;
		static unsigned long MoveDelay = 0;
		
		
		if ((int32_t) (millis() - servo_timer) >= 0) {
			if (CurrPosition == SERVO_START_POS) {
				Servo_Move(SERVO_END_POS);
				//DEBUG_PRINT(F("move end 100 "));
				CurrPosition = SERVO_END_POS;
			} else if (CurrPosition == SERVO_END_POS) {
				Servo_Move(SERVO_START_POS);
				CurrPosition = SERVO_START_POS;
				//DEBUG_PRINT(F("move start 0"));
			}
			//DEBUG_PRINT(F("Servo moving"));
            servo_timer += ( (SERVO_PERIOD * 1000L) + MoveDelay);
            MoveDelay = 0;
			//delay(100);
			//DEBUG_PRINT(F("\nAPRS message sent. GPS signal good."));
		} else {
			//MoveDelay = millis();
		}		
	} else {
		//DEBUG_PRINT(F("Servo not on."));
		//debug stuff here
	}
}