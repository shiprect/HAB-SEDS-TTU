#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H


#define DEBUG_UART Serial


#ifdef DEBUG
#define DEBUG_PRINT(str)            \
   DEBUG_UART.println(str);
#else
#define DEBUG_PRINT(str)
#endif

#ifdef APRS_DEBUG
#define DEBUG_APRS(str)       \
   DEBUG_UART.print(millis()/1000); \
   DEBUG_UART.print(F(": "));       \
   DEBUG_UART.print(__FUNCTION__);  \
   DEBUG_UART.print(__LINE__);      \
   DEBUG_UART.print(F(' '));        \
   DEBUG_UART.println(str);
#else
#define DEBUG_APRS(str)
#endif

#ifdef AX25_DEBUG
#define DEBUG_AX25(str)       \
   DEBUG_UART.print(millis()/1000); \
   DEBUG_UART.print(F(": "));       \
   DEBUG_UART.print(__FUNCTION__);  \
   DEBUG_UART.print(F("() in "));   \
   DEBUG_UART.print(__FILE__);      \
   DEBUG_UART.print(F(':'));        \
   DEBUG_UART.print(__LINE__);      \
   DEBUG_UART.print(F(' '));        \
   DEBUG_UART.println(str);
#else
#define DEBUG_AX25(str)
#endif

#ifdef DEBUG_GPS_BASIC
#define DEBUG_GPS_BASIC(str)            \
   DEBUG_UART.print(str);
#else
#define DEBUG_GPS_BASIC(str)
#endif

#ifdef GPS_ADV_DEBUG
#define DEBUG_GPS_ADV(str)        \
   DEBUG_UART.print(str);
#else
#define DEBUG_GPS_ADV(str)
#endif

#ifdef BMP_DEBUG
#define DEBUG_BMP(str)      \
   DEBUG_UART.print(str);
#else
#define DEBUG_BMP(str)
#endif

#ifdef AFSK_DEBUG
#define DEBUG_AFSK(str)       \
   DEBUG_UART.print(millis()/1000); \
   DEBUG_UART.print(F(": "));       \
   DEBUG_UART.print(__FUNCTION__);  \
   DEBUG_UART.print(F("() in "));   \
   DEBUG_UART.print(__FILE__);      \
   DEBUG_UART.print(F(':'));        \
   DEBUG_UART.print(__LINE__);      \
   DEBUG_UART.print(F(' '));        \
   DEBUG_UART.println(str);
#else
#define DEBUG_AFSK(str)
#endif

#ifdef RTTY_DEBUG
#define RTTY_DEBUG(str)            \
   DEBUG_UART.print(str);
#else
#define RTTY_DEBUG(str)
#endif

#ifdef RESET_DEBUG
#define DEBUG_RESET(str)      \
   DEBUG_UART.print(millis()/1000); \
   DEBUG_UART.print(F(": "));       \
   DEBUG_UART.print(__FUNCTION__);  \
   DEBUG_UART.print(F("() in "));   \
   DEBUG_UART.print(__FILE__);      \
   DEBUG_UART.print(F(':'));        \
   DEBUG_UART.print(__LINE__);      \
   DEBUG_UART.print(F(' '));        \
   DEBUG_UART.println(str);
#else
#define DEBUG_RESET(str)
#endif


#endif