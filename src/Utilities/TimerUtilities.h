#ifndef __TIMERUTILITIES_H__
#define __TIMERUTILITIES_H__


struct SoftTimer_Struct {
	//**********************************
	//	Create an instance by calling:
	//		timer myTimer =
	//		{
	//			0, 200UL, TRUE, TRUE	// lastMillis, waitMillis, IsRepeatable, IsEnabled
	//		};
	//
	//	Update the timer via:
	//		myTimer.CheckTime()
	//
	//	Note that the timer will disable itself if IsRepeatable = FALSE
	//**********************************

	unsigned long lastMillis;   // The time this "timer" was (re)started
	unsigned long waitMillis;   // Delay time(mS) we are looking for
	bool IsRepeatable;          // Does the timer repeat itself
	bool IsEnabled;             // Is "this timer" enabled/allowed to be accessed

	bool CheckTime() {
		if ( IsEnabled
		     && (( millis() - lastMillis ) >= waitMillis )) {  // Run if Timer enabled and one period has passed
			if ( IsRepeatable ) {  //Should the timer reset or expire
				lastMillis += waitMillis;
			}
			else {
				IsEnabled = FALSE;  // Required to ensure that the timer does not execute when millis() runs over
			}
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
};


#endif //__TIMERUTILITIES_H__