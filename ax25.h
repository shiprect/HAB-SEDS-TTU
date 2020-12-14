#ifndef __AX25_H__
#define __AX25_H__

#include <stdint.h>

struct PathAddress;


void ax25_initBuffer(uint8_t * buf, const int bufSize);

void ax25_send_header(const struct PathAddress * const paths,
                      const uint16_t nPaths,
                      const uint16_t txDelay);

void ax25_send_byte(uint8_t a_byte);

void ax25_send_string(const char * const string);

void ax25_send_footer();

unsigned int ax25_getPacketSize();


#endif