#include "Status.hpp"



//time after ballon is rising
// 




void Status::CheckSensors() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
}


//if gps `> 100
//start timer here
void Status::CheckRising() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	if(bmp.GetAltitude() > 100) {
		Rising = TRUE;
		DEBUG_PRINT(F("Rising"));
	}
}


// same for gps
void Status::CheckFalling() {
	if(Rising) {
		if(bmp.GetAltitude() < (bmp.GetMaxAltitude() - 100) ) {
			Falling = TRUE;
			DEBUG_PRINT(F("Falling"));
		}
	}
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
}

// less than 1000 or for bmp

void Status::CheckLanded() {
	if(Falling) {
		if( (bmp.GetAltitude() < 1000) or (gps.GetAltitude() < 1000) ) {
			Landed = TRUE;
			DEBUG_PRINT(F("Landed"));
		}
	}
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
}

void Status::CheckServo() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	if(Rising) {
		if( (bmp.GetAltitude() > 31000) and (gps.GetAltitude() > 31000) ) {
			ServoStatus = ON;
			CutServo.Servo_Status(ON);
		}
		else if (millis() > 5340000 ) {
			ServoStatus = ON;
			CutServo.Servo_Status(ON);
		}
	}
}

void Status::CheckStatus() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	CheckRising();
	CheckFalling();
	CheckLanded();
	
	CheckAPRS();
}

void Status::CheckAPRS() {
	
	    
	
}

bool Status::IsValidBMP() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	return ValidBMP;
}

bool Status::IsValidSD() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	return ValidSD;
}

bool Status::IsRising() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	return Rising;
}

bool Status::IsFalling() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	return Falling;
}

bool Status::IsLanded() {
	return Landed;
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
}

bool Status::IsServoOn() {
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
	return ServoStatus;
}

bool Status::WhatIsStatus() {
	return WhatStatus;
	//DEBUG_BMP(F("Baseline Pressure: "));  DEBUG_BMP(event.pressure);
}

