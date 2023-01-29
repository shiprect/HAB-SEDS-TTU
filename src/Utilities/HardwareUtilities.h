#ifndef __HARDWAREUTILS_H__
#define __HARDWAREUTILS_H__


#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

//TODO::Should we get rid of this or add an STM version???
#if EMBEDDED__ARDUINO
	#define LED_TOGGLE( x ) digitalWrite(x, digitalRead(x) ? LOW : HIGH)
	#define LED_ON( x ) digitalWrite(x, HIGH)
	#define LED_OFF( x ) digitalWrite(x, LOW)
#endif


#endif