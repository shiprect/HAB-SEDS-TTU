#ifndef __DEBUGUTILS_H__
#define __DEBUGUTILS_H__

// #include <cstdio>
// #include <iostream>
// #include <cstring>

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

// TODO::For Chris - Add fprintf() version of DEBUG
// This should follow the same macro format as DEBUG__SERIAL
// DEBUG__FPRINTF already exists in ProjectConfig.hpp
// As a note, the do{}while() is necessary for correct compilation
// error checking when the EN_DEBUG macro is set FALSE
// In APRS debug I also have macro examples that will do things
// like printing the line, function, etc. Having the ability to toggle
// all of these using macros would be extremely useful. At the very least,
// having the prints always print the line number at the beginning of the
// print statements would be nice.`
#if DEBUG__FPRINTF
// 	#if DEBUG_CX == cout	//NOTE: This is still broken until tested on another board besides the Teensy
// 		#define DEBUG_PRINT(str)\
	// 			do {\
	// 				if (EN_PRINT_DEBUG) {\
	// 					DEBUG_CX << str << endl;\
	// 				}\
	// 			} while (0)
// 	#else	//if DEBUG_CX == STDOUT_FILENO or STDERR_FILENO
// 		//dprintf is a variant that uses a file descriptor instead of a FILE*
// 		//i.e. uses STDOUT_FILENO/STDERR_FILENO instead of stdout/stderr
// 		//NOTE: This is still broken until tested on another board besides the Teensy
// 		#define DEBUG_PRINT(str)\
	// 			do {\
	// 				if (EN_PRINT_DEBUG) {\
	// 					dprintf(DEBUG_CX, str);\
	// 				}\
	// 			} while (0)
// 	#endif
#endif


#endif //DEBUGUTILS