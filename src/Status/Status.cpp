#include "Status.hpp"


void Status::CheckSensors() {
	
	
}


void Status::CheckRising() {
	// if(bmp.GetAltitude() > 100) {
		// Rising = TRUE;
		// DEBUG_PRINT(F("Rising"));
	// }
	if( (bmp.GetAltitude() > 500) or (gps.GetAltitude() > 500) ) {
		Rising = TRUE;
		Launched = TRUE;///////////////fix this
		DEBUG_PRINT(F("Rising"));
		TimeSinceLaunch = millis() + (SERVO_CUT_TIMEOUT * 1000L);
	}
}


void Status::CheckFalling() {
	// if(Rising) {
		// if(bmp.GetAltitude() < (bmp.GetMaxAltitude() - 100) ) {
			// Falling = TRUE;
			// DEBUG_PRINT(F("Falling"));
		// }
	// }
	
	if(Rising) {
		if( (bmp.GetAltitude() < (bmp.GetMaxAltitude() - 100)) )  {
			Falling = TRUE;
			//DEBUG_PRINT(F("Falling"));
		}
		else if ( (gps.GetAltitude() < (gps.GetMaxAltitude() - 100)) )  {
			Falling = TRUE;
			//DEBUG_PRINT(F("Falling"));
		}
	}
}


void Status::CheckLanded() {
	if(Falling) {
		if( (bmp.GetAltitude() < 1000) or (gps.GetAltitude() < 1000) ) {
			Landed = TRUE;
			//DEBUG_PRINT(F("Landed"));
		}
	}
}


void Status::CheckServo() {
	if(Rising) {
		if( (bmp.GetAltitude() > SERVO_CUT_ALT) and (gps.GetAltitude() > SERVO_CUT_ALT) ) {
			ServoStatus = ON;
			CutServo.Servo_Status(ON);
		}
		else if (millis() > TimeSinceLaunch ) {
			ServoStatus = ON;
			CutServo.Servo_Status(ON);
		}
	}
}

void Status::CheckStatus() {
	CheckSensors();
	
	CheckRising();
	CheckFalling();
	CheckLanded();
	
	CheckAPRS();
}

void Status::CheckAPRS() {
	
	
	
}

bool Status::IsValidBMP() {
	return ValidBMP;
}

bool Status::IsValidSD() {
	return ValidSD;
}

bool Status::IsLaunched()  {
	return Launched;
}

bool Status::IsRising() {
	return Rising;
}

bool Status::IsFalling() {
	return Falling;
}

bool Status::IsLanded() {
	return Landed;
}

bool Status::IsServoOn() {
	return ServoStatus;
}
