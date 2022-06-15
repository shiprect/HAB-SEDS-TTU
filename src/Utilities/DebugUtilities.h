#ifndef __DEBUGUTILS_H__
#define __DEBUGUTILS_H__


#ifdef DEBUG__SERIAL
	#define DEBUG_UART Serial

	#define DEBUG_PRINT(str)\
		do { if(EN_PRINT_DEBUG) DEBUG_UART.println(str); } while(0)

	/*#ifdef APRS_DEBUG
		#define DEBUG_APRS(str)					\
				DEBUG_UART.print(millis()/1000);\
				DEBUG_UART.print(F(": "));		\
				DEBUG_UART.print(__FUNCTION__);	\
				DEBUG_UART.print(__LINE__);		\
				DEBUG_UART.print(F(' '));		\
				DEBUG_UART.println(str);
	#else
		#define DEBUG_APRS(str)
	#endif*/
#endif


#endif