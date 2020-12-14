#ifndef __AFSK_H__
#define __AFSK_H__

#include <stdint.h>

#include "config.h"


// Exported functions
void afsk_setup(const uint8_t pttPin,           // Use PTT pin, 0 = do not use PTT
                const uint16_t pttDelay,        // ms to wait after PTT to transmit
                const uint32_t toneLength,
                const uint32_t p_silenceLength);
                
void afsk_set_buffer(const uint8_t * const buffer, const uint16_t len);

void afsk_start();

int afsk_busy();

uint16_t afsk_getTxDelay();


#endif